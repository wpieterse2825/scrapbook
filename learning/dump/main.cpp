#include <stdarg.h>
#include <string.h>
#include <math.h>

#include <iostream>

#include <SDL2/SDL.h>

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

typedef struct world_doom_line_s {
    point_2d_t   start_point;
    point_2d_t   end_point;
    int          flags;
    int          special;
    int          tag;
    world_side_t side[2];
} world_doom_line_t;

typedef struct world_thing_s {
    point_2d_t origin;
    int        angle;
    int        type;
    int        options;
} world_thing_t;

const char* available_maps[] = {
  "learning/dump/doom_1/e1m1.dwd",  "learning/dump/doom_1/e1m2.dwd",  "learning/dump/doom_1/e1m3.dwd",  "learning/dump/doom_1/e1m4.dwd",
  "learning/dump/doom_1/e1m5.dwd",  "learning/dump/doom_1/e1m6.dwd",  "learning/dump/doom_1/e1m7.dwd",  "learning/dump/doom_1/e1m8.dwd",
  "learning/dump/doom_1/e1m9.dwd",  "learning/dump/doom_1/e2m1.dwd",  "learning/dump/doom_1/e2m2.dwd",  "learning/dump/doom_1/e2m3.dwd",
  "learning/dump/doom_1/e2m4.dwd",  "learning/dump/doom_1/e2m5.dwd",  "learning/dump/doom_1/e2m6.dwd",  "learning/dump/doom_1/e2m7.dwd",
  "learning/dump/doom_1/e2m8.dwd",  "learning/dump/doom_1/e2m9.dwd",  "learning/dump/doom_1/e3m1.dwd",  "learning/dump/doom_1/e3m2.dwd",
  "learning/dump/doom_1/e3m3.dwd",  "learning/dump/doom_1/e3m4.dwd",  "learning/dump/doom_1/e3m5.dwd",  "learning/dump/doom_1/e3m6.dwd",
  "learning/dump/doom_1/e3m7.dwd",  "learning/dump/doom_1/e3m8.dwd",  "learning/dump/doom_1/e3m9.dwd",  "learning/dump/doom_2/map01.dwd",
  "learning/dump/doom_2/map02.dwd", "learning/dump/doom_2/map03.dwd", "learning/dump/doom_2/map04.dwd", "learning/dump/doom_2/map05.dwd",
  "learning/dump/doom_2/map06.dwd", "learning/dump/doom_2/map07.dwd", "learning/dump/doom_2/map08.dwd", "learning/dump/doom_2/map09.dwd",
  "learning/dump/doom_2/map10.dwd", "learning/dump/doom_2/map11.dwd", "learning/dump/doom_2/map12.dwd", "learning/dump/doom_2/map13.dwd",
  "learning/dump/doom_2/map14.dwd", "learning/dump/doom_2/map15.dwd", "learning/dump/doom_2/map16.dwd", "learning/dump/doom_2/map17.dwd",
  "learning/dump/doom_2/map18.dwd", "learning/dump/doom_2/map19.dwd", "learning/dump/doom_2/map20.dwd", "learning/dump/doom_2/map21.dwd",
  "learning/dump/doom_2/map22.dwd", "learning/dump/doom_2/map23.dwd", "learning/dump/doom_2/map24.dwd", "learning/dump/doom_2/map25.dwd",
  "learning/dump/doom_2/map26.dwd", "learning/dump/doom_2/map27.dwd", "learning/dump/doom_2/map28.dwd", "learning/dump/doom_2/map29.dwd",
  "learning/dump/doom_2/map30.dwd", "learning/dump/doom_2/map31.dwd", "learning/dump/doom_2/map32.dwd", "learning/dump/doom_2/map34.dwd",
  "learning/dump/doom_2/map35.dwd", "learning/dump/doom_2/map36.dwd"};

int available_map_count = sizeof(available_maps) / sizeof(const char*);

storage_t* doom_line_storage = nullptr;
storage_t* thing_storage     = nullptr;
storage_t* sector_storage    = nullptr;

bool          running              = true;
int           screen_width         = 1280;
int           screen_height        = 720;
SDL_Window*   screen               = nullptr;
SDL_Renderer* renderer             = nullptr;
SDL_Event     event                = {};
int           renderer_x_size      = 0;
int           renderer_y_size      = 0;
int           automap_scale_factor = 8;
float         camera_x             = 0.0f;
float         camera_y             = 0.0f;
bool          reload_map           = true;
int           map_index            = 0;
int           sector_count         = -1;
int           sector_debug         = -1;

void Error(const char* format, ...) {
    va_list arguments;

    va_start(arguments, format);
    vprintf(format, arguments);
    va_end(arguments);
    printf("\n");

    exit(1);
}

world_doom_line_t* ReadLine(FILE* map_file, int line_index, world_doom_line_t* world_line) {
    world_side_t*        doom_line_side        = nullptr;
    sector_definition_t* doom_line_side_sector = nullptr;
    int                  side_count            = 1;

    memset(world_line, 0, sizeof(world_doom_line_t));

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
        doom_line_side = &world_line->side[index];
        if (fscanf(map_file,
                   "    %d (%d : %s / %s / %s )\n",
                   &doom_line_side->first_row,
                   &doom_line_side->first_column,
                   doom_line_side->top_texture,
                   doom_line_side->bottom_texture,
                   doom_line_side->middle_texture) != 5) {
            Error("Failed to read line side definition.");
        }

        doom_line_side_sector = &doom_line_side->sector_definition;
        if (fscanf(map_file,
                   "    %d : %s %d : %s %d %d %d\n",
                   &doom_line_side_sector->floor_height,
                   doom_line_side_sector->floor_texture,
                   &doom_line_side_sector->ceiling_height,
                   doom_line_side_sector->ceiling_texture,
                   &doom_line_side_sector->light_level,
                   &doom_line_side_sector->special,
                   &doom_line_side_sector->tag) != 7) {
            Error("Failed to read line side sector defintion.");
        }

        if (!strcmp(doom_line_side_sector->floor_texture, "-")) {
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

void ReadMap(FILE* file) {
    int                line_count    = 0;
    int                thing_count   = 0;
    world_doom_line_t* current_line  = nullptr;
    world_thing_t*     current_thing = nullptr;

    if (fscanf(file, "\nlines:%d\n", &line_count) != 1) {
        Error("Can't read line count.");
    }

    doom_line_storage        = (storage_t*)malloc(sizeof(storage_t));
    doom_line_storage->data  = (world_doom_line_t*)calloc(line_count, sizeof(world_doom_line_t));
    doom_line_storage->size  = sizeof(world_doom_line_t);
    doom_line_storage->count = 0;
    current_line             = (world_doom_line_t*)doom_line_storage->data;

    for (int index = 0; index < line_count; index++) {
        ReadLine(file, index, current_line);

        doom_line_storage->count++;
        current_line++;
    }

    if (fscanf(file, "\nthings:%d\n", &thing_count) != 1) {
        Error("Can't read thing count.");
    }

    thing_storage        = (storage_t*)malloc(sizeof(storage_t));
    thing_storage->data  = (world_thing_t*)calloc(thing_count, sizeof(world_thing_t));
    thing_storage->size  = sizeof(world_thing_t);
    thing_storage->count = thing_count;
    current_thing        = (world_thing_t*)thing_storage->data;

    for (int index = 0; index < thing_count; index++) {
        ReadThing(file, index, current_thing);
        current_thing++;
    }
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
    world_doom_line_t* lines      = (world_doom_line_t*)doom_line_storage->data;
    int                line_count = doom_line_storage->count;

    sector_storage        = (storage_t*)malloc(sizeof(storage_t));
    sector_storage->data  = (sector_definition_t*)calloc(line_count * 2, sizeof(sector_definition_t));
    sector_storage->size  = sizeof(sector_definition_t);
    sector_storage->count = 0;

    for (int index = 0; index < line_count; index++) {
        world_doom_line_t* current_line = &lines[index];

        current_line->side[0].sector = GenerateSectorID(&current_line->side[0].sector_definition);
        if (current_line->flags & LINE_FLAG_TWO_SIDED) {
            current_line->side[1].sector = GenerateSectorID(&current_line->side[1].sector_definition);
        }
    }
}

void GenerateCameraCenter() {
    world_doom_line_t* lines      = (world_doom_line_t*)doom_line_storage->data;
    int                line_count = doom_line_storage->count;

    float minimum_x = 128000.0f;
    float minimum_y = 128000.0f;
    float maximum_x = -128000.0f;
    float maximum_y = -128000.0f;

    for (int index = 0; index < line_count; index++) {
        world_doom_line_t* current_line = &lines[index];
        point_2d_t*        start        = &current_line->start_point;
        point_2d_t*        end          = &current_line->end_point;

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

void InitializeSDL() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        Error("Could not init SDL: %s.", SDL_GetError());
    }

    screen = SDL_CreateWindow("DOOM", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screen_width, screen_height, 0);
    if (screen == nullptr) {
        Error("Could not create window.");
    }

    renderer = SDL_CreateRenderer(screen, -1, SDL_RENDERER_SOFTWARE);
    if (renderer == nullptr) {
        Error("Could not create renderer.");
    }
}

void HandleSDLEvents() {
    while (SDL_PollEvent(&event) == true) {
        if (event.type == SDL_QUIT) {
            running = false;

            break;
        } else if (event.type == SDL_KEYUP) {
            if (event.key.keysym.sym == SDLK_ESCAPE) {
                running = false;

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

                if (sector_debug > sector_count) {
                    sector_debug = sector_count;
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
}

void ProcessMapChange() {
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

        if (doom_line_storage != nullptr) {
            free(doom_line_storage->data);
            free(doom_line_storage);

            doom_line_storage = nullptr;
        }

        std::cout << "Loading : " << map_name << std::endl;

        FILE* map_file = fopen(map_name, "rb");
        if (map_file == nullptr) {
            Error("Failed to open map : %s", map_name);
        }

        int version = 0;
        if (!fscanf(map_file, "WorldServer version %d\n", &version) || version != 4) {
            Error("ReadMap: not a version 4 doom map");
        }

        ReadMap(map_file);
        GenerateSectors();
        GenerateCameraCenter();

        fclose(map_file);

        automap_scale_factor = 8;
        camera_x             = (camera_x) - ((screen_width / 2) * automap_scale_factor);
        camera_y             = -(camera_y) - ((screen_height / 2) * automap_scale_factor);
        sector_debug         = -1;
        reload_map           = false;
    }
}

void RenderMapLineSetColorSectorDebug(world_doom_line_t* current_line) {
    int     side_0_sector_id = current_line->side[0].sector;
    int     side_1_sector_id = current_line->side[1].sector;
    uint8_t r                = 0;
    uint8_t g                = 0;
    uint8_t b                = 0;

    if (current_line->flags & LINE_FLAG_TWO_SIDED) {
        if (side_0_sector_id == sector_debug || side_1_sector_id == sector_debug) {
            r = 255;
            g = 0;
            b = 0;
        } else {
            r = 64;
            g = 64;
            b = 64;
        }
    } else if (side_0_sector_id == sector_debug) {
        r = 255;
        g = 0;
        b = 0;
    } else {
        r = 64;
        g = 64;
        b = 64;
    }

    SDL_SetRenderDrawColor(renderer, r, g, b, SDL_ALPHA_OPAQUE);
}

void RenderMapLineSetColorSector(world_doom_line_t* current_line) {
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

    int     sector_id = current_line->side[0].sector;
    uint8_t r         = colors[sector_id & 11][0];
    uint8_t g         = colors[sector_id & 11][1];
    uint8_t b         = colors[sector_id & 11][2];

    SDL_SetRenderDrawColor(renderer, r, g, b, SDL_ALPHA_OPAQUE);
}

void RenderMapLineSetColor(world_doom_line_t* current_line) {
    if (sector_debug >= 0) {
        RenderMapLineSetColorSectorDebug(current_line);
    } else {
        RenderMapLineSetColorSector(current_line);
    }
}

void RenderMapLines() {
    if (doom_line_storage == nullptr) {
        return;
    }

    if (doom_line_storage->data == nullptr) {
        return;
    }

    world_doom_line_t* lines      = (world_doom_line_t*)doom_line_storage->data;
    int                line_count = doom_line_storage->count;
    for (int index = 0; index < line_count; index++) {
        world_doom_line_t* current_line = &lines[index];
        point_2d_t         start        = current_line->start_point;
        point_2d_t         end          = current_line->end_point;

        RenderMapLineSetColor(current_line);

        SDL_RenderDrawLineF(renderer,
                            (start.x - camera_x) / automap_scale_factor,
                            (-start.y - camera_y) / automap_scale_factor,
                            (end.x - camera_x) / automap_scale_factor,
                            (-end.y - camera_y) / automap_scale_factor);
    }
}

void* ReadCompleteFile(const char* name, long* size) {
    std::cout << "Loading : " << name << std::endl;

    FILE* file = fopen(name, "rb");
    if (file == nullptr) {
        Error("Failed to open %s.", name);
    }

    fseek(file, 0, SEEK_END);
    *size = ftell(file);
    fseek(file, 0, SEEK_SET);

    void* buffer = malloc(*size);
    if (buffer == nullptr) {
        Error("Failed to allocate memory for %s.", name);
    }

    fread(buffer, 1, *size, file);

    fclose(file);

    return buffer;
}

typedef struct vertex_s {
    int16_t x;
    int16_t y;
} vertex_t;

typedef struct doom_line_s {
    int16_t start_vertex;
    int16_t end_vertex;
    int16_t flags;
    int16_t type;
    int16_t sector_tag;
    int16_t right_side;
    int16_t left_side;
} doom_line_t;

typedef struct hexen_line_s {
    int16_t start_vertex;
    int16_t end_vertex;
    int16_t flags;
    uint8_t special_type;
    uint8_t arguments[5];
    int16_t right_side;
    int16_t left_side;
} hexen_line_t;

typedef struct side_s {
    int16_t  texture_x_offset;
    int16_t  texture_y_offset;
    uint8_t  upper_texture[8];
    uint8_t  lower_texture[8];
    uint8_t  middle_texture[8];
    uint16_t sector;
} side_t;

typedef struct sector_s {
    int16_t floor_height;
    int16_t ceiling_height;
    uint8_t floor_texture[8];
    uint8_t ceiling_texture[8];
    int16_t light_level;
    int16_t sector_special;
    int16_t sector_tag;
} sector_t;

void ProcessMapChangeWAD() {
    if (reload_map == true) {
        const char* vertices_name = "learning/dump/hexen/map_01_vertices.lmp";
        const char* lines_name    = "learning/dump/hexen/map_01_lines.lmp";
        const char* sides_name    = "learning/dump/hexen/map_01_sides.lmp";
        const char* sectors_name  = "learning/dump/hexen/map_01_sectors.lmp";

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

        if (doom_line_storage != nullptr) {
            free(doom_line_storage->data);
            free(doom_line_storage);

            doom_line_storage = nullptr;
        }

        long vertices_size = 0;
        long lines_size    = 0;
        long sides_size    = 0;
        long sectors_size  = 0;

        void* vertices_buffer = ReadCompleteFile(vertices_name, &vertices_size);
        void* lines_buffer    = ReadCompleteFile(lines_name, &lines_size);
        void* sides_buffer    = ReadCompleteFile(sides_name, &sides_size);
        void* sectors_buffer  = ReadCompleteFile(sectors_name, &sectors_size);

        int vertices_count = vertices_size / sizeof(vertex_t);
        int lines_count    = lines_size / sizeof(hexen_line_t);
        int sides_count    = sides_size / sizeof(side_t);
        int sectors_count  = sectors_size / sizeof(sector_t);

        vertex_t*     vertices = (vertex_t*)vertices_buffer;
        hexen_line_t* lines    = (hexen_line_t*)lines_buffer;
        side_t*       sides    = (side_t*)sides_buffer;
        sector_t*     sectors  = (sector_t*)sectors_buffer;

        std::cout << " * Vertices : " << vertices_count << " - " << vertices_size << std::endl;
        std::cout << " * Lines    : " << lines_count << " - " << lines_size << std::endl;
        std::cout << " * Sides    : " << sides_count << " - " << sides_size << std::endl;
        std::cout << " * Sectors  : " << sectors_count << " - " << sectors_size << std::endl;

        doom_line_storage        = (storage_t*)malloc(sizeof(storage_t));
        doom_line_storage->data  = (world_doom_line_t*)calloc(lines_count, sizeof(world_doom_line_t));
        doom_line_storage->size  = sizeof(world_doom_line_t);
        doom_line_storage->count = 0;

        world_doom_line_t* global_lines = (world_doom_line_t*)doom_line_storage->data;
        for (int index = 0; index < lines_count; index++) {
            hexen_line_t*      current_load_line  = &lines[index];
            world_doom_line_t* current_world_line = &global_lines[index];

            current_world_line->start_point.x = vertices[current_load_line->start_vertex].x;
            current_world_line->start_point.y = vertices[current_load_line->start_vertex].y;
            current_world_line->end_point.x   = vertices[current_load_line->end_vertex].x;
            current_world_line->end_point.y   = vertices[current_load_line->end_vertex].y;
            current_world_line->flags         = current_load_line->flags;
            // current_world_line->special       = current_load_line->sector_tag;

            if (current_load_line->right_side != 0xFFFF) {
                side_t* current_side = &sides[current_load_line->right_side];

                if (current_side->sector > sector_count) {
                    sector_count = current_side->sector;
                }

                current_world_line->side[0].sector = current_side->sector;
            }

            if (current_load_line->left_side != 0xFFFF) {
                side_t* current_side = &sides[current_load_line->left_side];

                if (current_side->sector > sector_count) {
                    sector_count = current_side->sector;
                }

                current_world_line->side[1].sector = current_side->sector;
            }

            doom_line_storage->count++;
        }

        free(sectors_buffer);
        free(sides_buffer);
        free(lines_buffer);
        free(vertices_buffer);

        reload_map = false;
    }
}

int main(int argument_count, char** arguments) {
    InitializeSDL();

    while (running == true) {
        HandleSDLEvents();
        // ProcessMapChange();
        ProcessMapChangeWAD();

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        RenderMapLines();

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyWindow(screen);
    SDL_Quit();

    return 0;
}
