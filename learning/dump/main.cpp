#include <stdarg.h>
#include <string.h>
#include <math.h>

#include <iostream>

#include "tools/cpp/runfiles/runfiles.h"

#include <SDL2/SDL.h>

using bazel::tools::cpp::runfiles::Runfiles;

#define LINE_FLAG_TWO_SIDED 4

typedef struct storage_s {
    int   count;
    int   size;
    void* data;
} storage_t;

typedef struct point_2d_s {
    float x;
    float y;
} point_2d_t;

typedef struct sector_definition_s {
    int  floor_height;
    int  ceiling_height;
    char floor_texture[9];
    char ceiling_texture[9];
    int  light_level;
    int  special;
    int  tag;
} sector_definition_t;

typedef struct world_side_s {
    int                 first_row;
    int                 first_column;
    char                top_texture[9];
    char                bottom_texture[9];
    char                middle_texture[9];
    sector_definition_t sector_definition;
    int                 sector;
} world_side_t;

typedef struct world_line_s {
    point_2d_t   start_point;
    point_2d_t   end_point;
    int          flags;
    int          special;
    int          tag;
    world_side_t side[2];
} world_line_t;

typedef struct world_thing_s {
    point_2d_t origin;
    int        angle;
    int        type;
    int        options;
} world_thing_t;

storage_t* line_storage   = nullptr;
storage_t* thing_storage  = nullptr;
storage_t* sector_storage = nullptr;

const char* available_maps[] = {
  "scrapbook/learning/dump/doom_1/e1m1.dwd",  "scrapbook/learning/dump/doom_1/e1m2.dwd",  "scrapbook/learning/dump/doom_1/e1m3.dwd",
  "scrapbook/learning/dump/doom_1/e1m4.dwd",  "scrapbook/learning/dump/doom_1/e1m5.dwd",  "scrapbook/learning/dump/doom_1/e1m6.dwd",
  "scrapbook/learning/dump/doom_1/e1m7.dwd",  "scrapbook/learning/dump/doom_1/e1m8.dwd",  "scrapbook/learning/dump/doom_1/e1m9.dwd",
  "scrapbook/learning/dump/doom_1/e2m1.dwd",  "scrapbook/learning/dump/doom_1/e2m2.dwd",  "scrapbook/learning/dump/doom_1/e2m3.dwd",
  "scrapbook/learning/dump/doom_1/e2m4.dwd",  "scrapbook/learning/dump/doom_1/e2m5.dwd",  "scrapbook/learning/dump/doom_1/e2m6.dwd",
  "scrapbook/learning/dump/doom_1/e2m7.dwd",  "scrapbook/learning/dump/doom_1/e2m8.dwd",  "scrapbook/learning/dump/doom_1/e2m9.dwd",
  "scrapbook/learning/dump/doom_1/e3m1.dwd",  "scrapbook/learning/dump/doom_1/e3m2.dwd",  "scrapbook/learning/dump/doom_1/e3m3.dwd",
  "scrapbook/learning/dump/doom_1/e3m4.dwd",  "scrapbook/learning/dump/doom_1/e3m5.dwd",  "scrapbook/learning/dump/doom_1/e3m6.dwd",
  "scrapbook/learning/dump/doom_1/e3m7.dwd",  "scrapbook/learning/dump/doom_1/e3m8.dwd",  "scrapbook/learning/dump/doom_1/e3m9.dwd",
  "scrapbook/learning/dump/doom_2/map01.dwd", "scrapbook/learning/dump/doom_2/map02.dwd", "scrapbook/learning/dump/doom_2/map03.dwd",
  "scrapbook/learning/dump/doom_2/map04.dwd", "scrapbook/learning/dump/doom_2/map05.dwd", "scrapbook/learning/dump/doom_2/map06.dwd",
  "scrapbook/learning/dump/doom_2/map07.dwd", "scrapbook/learning/dump/doom_2/map08.dwd", "scrapbook/learning/dump/doom_2/map09.dwd",
  "scrapbook/learning/dump/doom_2/map10.dwd", "scrapbook/learning/dump/doom_2/map11.dwd", "scrapbook/learning/dump/doom_2/map12.dwd",
  "scrapbook/learning/dump/doom_2/map13.dwd", "scrapbook/learning/dump/doom_2/map14.dwd", "scrapbook/learning/dump/doom_2/map15.dwd",
  "scrapbook/learning/dump/doom_2/map16.dwd", "scrapbook/learning/dump/doom_2/map17.dwd", "scrapbook/learning/dump/doom_2/map18.dwd",
  "scrapbook/learning/dump/doom_2/map19.dwd", "scrapbook/learning/dump/doom_2/map20.dwd", "scrapbook/learning/dump/doom_2/map21.dwd",
  "scrapbook/learning/dump/doom_2/map22.dwd", "scrapbook/learning/dump/doom_2/map23.dwd", "scrapbook/learning/dump/doom_2/map24.dwd",
  "scrapbook/learning/dump/doom_2/map25.dwd", "scrapbook/learning/dump/doom_2/map26.dwd", "scrapbook/learning/dump/doom_2/map27.dwd",
  "scrapbook/learning/dump/doom_2/map28.dwd", "scrapbook/learning/dump/doom_2/map29.dwd", "scrapbook/learning/dump/doom_2/map30.dwd",
  "scrapbook/learning/dump/doom_2/map31.dwd", "scrapbook/learning/dump/doom_2/map32.dwd", "scrapbook/learning/dump/doom_2/map34.dwd",
  "scrapbook/learning/dump/doom_2/map35.dwd", "scrapbook/learning/dump/doom_2/map36.dwd"};

int available_map_count = sizeof(available_maps) / sizeof(const char*);

float player_start_x       = 0.0f;
float player_start_y       = 0.0f;
bool  reload_map           = true;
int   map_index            = 0;
float camera_x             = 0.0f;
float camera_y             = 0.0f;
int   automap_scale_factor = 8;
int   renderer_x_size      = 0;
int   renderer_y_size      = 0;
int   sector_debug         = -1;

void Error(const char* format, ...) {
    va_list arguments;

    va_start(arguments, format);
    vprintf(format, arguments);
    va_end(arguments);
    printf("\n");

    exit(1);
}

world_line_t* ReadLine(FILE* map_file, int line_index, world_line_t* world_line) {
    world_side_t*        line_side        = nullptr;
    sector_definition_t* line_side_sector = nullptr;
    int                  side_count       = 1;

    memset(world_line, 0, sizeof(world_line_t));

    if (fscanf(map_file,
               "(%f,%f) to (%f,%f) : %d : %d : %d\n",
               &world_line->start_point.x,
               &world_line->start_point.y,
               &world_line->end_point.x,
               &world_line->end_point.y,
               &world_line->flags,
               &world_line->special,
               &world_line->tag) != 7) {
        Error("Failed to read line definition.");
    }

    if (world_line->flags & LINE_FLAG_TWO_SIDED) {
        side_count = 2;
    }

    for (int index = 0; index < side_count; index++) {
        line_side = &world_line->side[index];
        if (fscanf(map_file,
                   "    %d (%d : %s / %s / %s )\n",
                   &line_side->first_row,
                   &line_side->first_column,
                   line_side->top_texture,
                   line_side->bottom_texture,
                   line_side->middle_texture) != 5) {
            Error("Failed to read line side definition.");
        }

        line_side_sector = &line_side->sector_definition;
        if (fscanf(map_file,
                   "    %d : %s %d : %s %d %d %d\n",
                   &line_side_sector->floor_height,
                   line_side_sector->floor_texture,
                   &line_side_sector->ceiling_height,
                   line_side_sector->ceiling_texture,
                   &line_side_sector->light_level,
                   &line_side_sector->special,
                   &line_side_sector->tag) != 7) {
            Error("Failed to read line side sector defintion.");
        }

        if (!strcmp(line_side_sector->floor_texture, "-")) {
            printf("WARNING: Line %i has invalid sector definition\n", line_index);
        }
    }

    return world_line;
}

world_thing_t* ReadThing(FILE* map_file, int thing_index, world_thing_t* world_thing) {
    int x = 0;
    int y = 0;

    memset(world_thing, 0, sizeof(*world_thing));

    if (fscanf(map_file, "(%i,%i, %d) :%d, %d\n", &x, &y, &world_thing->angle, &world_thing->type, &world_thing->options) != 5) {
        Error("Failed to read thing definition.");
    }

    world_thing->origin.x = x;
    world_thing->origin.y = y;

    return world_thing;
}

void LoadMap(FILE* file) {
    int            line_count    = 0;
    int            thing_count   = 0;
    world_line_t*  current_line  = nullptr;
    world_thing_t* current_thing = nullptr;

    if (fscanf(file, "\nlines:%d\n", &line_count) != 1) {
        Error("Can't read line count.");
    }

    // printf("Found %i lines\n", line_count);

    line_storage        = (storage_t*)malloc(sizeof(storage_t));
    line_storage->data  = (world_line_t*)calloc(line_count, sizeof(world_line_t));
    line_storage->size  = sizeof(world_line_t);
    line_storage->count = 0;
    current_line        = (world_line_t*)line_storage->data;

    for (int index = 0; index < line_count; index++) {
        // printf(" - Reading line #%d\r", index);

        ReadLine(file, index, current_line);

        line_storage->count++;
        current_line++;
    }

    // printf("\n");

    if (fscanf(file, "\nthings:%d\n", &thing_count) != 1) {
        Error("Can't read thing count.");
    }

    // printf("Found %i things\n", thing_count);

    thing_storage        = (storage_t*)malloc(sizeof(storage_t));
    thing_storage->data  = (world_thing_t*)calloc(thing_count, sizeof(world_thing_t));
    thing_storage->size  = sizeof(world_thing_t);
    thing_storage->count = thing_count;
    current_thing        = (world_thing_t*)thing_storage->data;

    for (int index = 0; index < thing_count; index++) {
        // printf(" - Reading thing #%d\r", index);

        ReadThing(file, index, current_thing);
        current_thing++;
    }

    // printf("\n");
}

int GenerateSectorID(sector_definition_t* sector) {
    sector_definition_t* sectors        = (sector_definition_t*)sector_storage->data;
    int                  sector_count   = sector_storage->count;
    int                  index          = 0;
    sector_definition_t* current_sector = nullptr;

    for (index = 0; index < sector_count; index++) {
        current_sector = &sectors[index];

        if (memcmp(sector, current_sector, sizeof(sector_definition_t)) == 0) {
            return index;
        }
    }

    current_sector = &sectors[index];
    memcpy(current_sector, sector, sizeof(sector_definition_t));

    sector_storage->count++;

    return index;
}

void GenerateSectors() {
    world_line_t* lines      = (world_line_t*)line_storage->data;
    int           line_count = line_storage->count;

    sector_storage        = (storage_t*)malloc(sizeof(storage_t));
    sector_storage->data  = (sector_definition_t*)calloc(line_count * 2, sizeof(sector_definition_t));
    sector_storage->size  = sizeof(sector_definition_t);
    sector_storage->count = 0;

    for (int index = 0; index < line_count; index++) {
        world_line_t* current_line = &lines[index];

        current_line->side[0].sector = GenerateSectorID(&current_line->side[0].sector_definition);
        if (current_line->flags & LINE_FLAG_TWO_SIDED) {
            current_line->side[1].sector = GenerateSectorID(&current_line->side[1].sector_definition);
        }
    }
}

void QueryPlayerStart() {
    world_line_t* lines      = (world_line_t*)line_storage->data;
    int           line_count = line_storage->count;

    float minimum_x = 128000.0f;
    float minimum_y = 128000.0f;
    float maximum_x = -128000.0f;
    float maximum_y = -128000.0f;

    for (int index = 0; index < line_count; index++) {
        world_line_t* current_line = &lines[index];
        point_2d_t*   start        = &current_line->start_point;
        point_2d_t*   end          = &current_line->end_point;

        if (start->x < minimum_x) {
            minimum_x = start->x;
        }

        if (start->x > maximum_x) {
            maximum_x = start->x;
        }

        if (start->y < minimum_y) {
            minimum_y = start->y;
        }

        if (start->y > maximum_y) {
            maximum_y = start->y;
        }

        if (end->x < minimum_x) {
            minimum_x = end->x;
        }

        if (end->x > maximum_x) {
            maximum_x = end->x;
        }

        if (end->y < minimum_y) {
            minimum_y = end->y;
        }

        if (end->y > maximum_y) {
            maximum_y = end->y;
        }
    }

    camera_x = (minimum_x + maximum_x) / 2.0f;
    camera_y = (minimum_y + maximum_y) / 2.0f;
}

void UniqueSectorColor(int sector_id, uint8_t& r, uint8_t& g, uint8_t& b) {
    uint8_t colors[11][3] = {
      {255, 0, 0},
      {255, 128, 0},
      {255, 0, 128},
      {128, 255, 0},
      {0, 255, 0},
      {0, 255, 128},
      {128, 0, 255},
      {0, 128, 255},
      {255, 128, 128},
      {128, 255, 128},
      {128, 128, 255},
    };

    r = colors[sector_id & 11][0];
    g = colors[sector_id & 11][1];
    b = colors[sector_id & 11][2];
}

int main(int argument_count, char** arguments) {
    std::string               runfiles_error {""};
    std::unique_ptr<Runfiles> runfiles {Runfiles::Create(arguments[0], &runfiles_error)};

    SDL_Window*   screen   = nullptr;
    SDL_Renderer* renderer = nullptr;
    SDL_Event     event;

    if (runfiles == nullptr) {
        Error("Failed to initialize run-files : %s", runfiles_error.c_str());
    }

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "Could not init SDL: %s\n", SDL_GetError());
        return 1;
    }

    int screen_width  = 1280;
    int screen_height = 720;

    screen = SDL_CreateWindow("DOOM", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screen_width, screen_height, 0);
    if (screen == nullptr) {
        fprintf(stderr, "Could not create window\n");
        return 1;
    }

    renderer = SDL_CreateRenderer(screen, -1, SDL_RENDERER_SOFTWARE);
    if (renderer == nullptr) {
        fprintf(stderr, "Could not create renderer\n");
        return 1;
    }

    while (true) {
        if (SDL_PollEvent(&event) == true) {
            if (event.type == SDL_QUIT) {
                break;
            } else if (event.type == SDL_KEYUP) {
                if (event.key.keysym.sym == SDLK_ESCAPE) {
                    break;
                } else if (event.key.keysym.sym == SDLK_q) {
                    map_index--;
                    if (map_index < 0) {
                        map_index = available_map_count - 1;
                    }

                    reload_map = true;
                } else if (event.key.keysym.sym == SDLK_w) {
                    map_index++;
                    if (map_index >= available_map_count) {
                        map_index = 0;
                    }

                    reload_map = true;
                } else if (event.key.keysym.sym == SDLK_a) {
                    automap_scale_factor += 1;
                } else if (event.key.keysym.sym == SDLK_s) {
                    automap_scale_factor -= 1;
                } else if (event.key.keysym.sym == SDLK_z) {
                    sector_debug--;
                    if (sector_debug < -1) {
                        sector_debug = -1;
                    }
                } else if (event.key.keysym.sym == SDLK_x) {
                    sector_debug++;
                    if (sector_debug > (sector_storage->count - 1)) {
                        sector_debug = sector_storage->count - 1;
                    }
                } else if (event.key.keysym.sym == SDLK_c) {
                    sector_debug = -1;
                }
            } else if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_LEFT) {
                    camera_x -= 32;
                } else if (event.key.keysym.sym == SDLK_RIGHT) {
                    camera_x += 32;
                }

                if (event.key.keysym.sym == SDLK_UP) {
                    camera_y -= 32;
                } else if (event.key.keysym.sym == SDLK_DOWN) {
                    camera_y += 32;
                }
            }
        }

        if (reload_map == true) {
            const char* map_name = available_maps[map_index];

            if (sector_storage != nullptr) {
                free(sector_storage->data);
                free(sector_storage);

                sector_storage = nullptr;
            }

            if (thing_storage != nullptr) {
                free(thing_storage->data);
                free(thing_storage);

                thing_storage = nullptr;
            }

            if (line_storage != nullptr) {
                free(line_storage->data);
                free(line_storage);

                line_storage = nullptr;
            }

            std::cout << "Loading : " << map_name << std::endl;

            FILE* map_file = fopen(runfiles->Rlocation(map_name).c_str(), "rb");
            if (map_file == nullptr) {
                Error("Failed to open map : %s", map_name);
            }

            int version = 0;
            if (!fscanf(map_file, "WorldServer version %d\n", &version) || version != 4) {
                Error("LoadMap: not a version 4 doom map");
            }

            LoadMap(map_file);
            GenerateSectors();
            QueryPlayerStart();

            fclose(map_file);

            automap_scale_factor = 8;
            camera_x             = (camera_x) - ((screen_width / 2) * automap_scale_factor);
            camera_y             = -(camera_y) - ((screen_height / 2) * automap_scale_factor);
            sector_debug         = -1;
            reload_map           = false;
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        world_line_t* lines      = (world_line_t*)line_storage->data;
        int           line_count = line_storage->count;
        for (int index = 0; index < line_count; index++) {
            world_line_t* current_line = &lines[index];
            point_2d_t    start        = current_line->start_point;
            point_2d_t    end          = current_line->end_point;

            uint8_t r = 0;
            uint8_t g = 0;
            uint8_t b = 0;

            if (sector_debug >= 0) {
                if (current_line->flags & LINE_FLAG_TWO_SIDED) {
                    if (current_line->side[0].sector == sector_debug || current_line->side[1].sector == sector_debug) {
                        r = 255;
                        g = 0;
                        b = 0;
                    } else {
                        r = 64;
                        g = 64;
                        b = 64;
                    }
                } else if (current_line->side[0].sector == sector_debug) {
                    r = 255;
                    g = 0;
                    b = 0;
                } else {
                    r = 64;
                    g = 64;
                    b = 64;
                }
            } else {
                UniqueSectorColor(current_line->side[0].sector, r, g, b);
            }

            SDL_SetRenderDrawColor(renderer, r, g, b, SDL_ALPHA_OPAQUE);

            SDL_RenderDrawLineF(renderer,
                                (start.x - camera_x) / automap_scale_factor,
                                (-start.y - camera_y) / automap_scale_factor,
                                (end.x - camera_x) / automap_scale_factor,
                                (-end.y - camera_y) / automap_scale_factor);
        }

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyWindow(screen);
    SDL_Quit();

    return 0;
}
