#include <stdio.h>

#include <iostream>

#include <SDL2/SDL.h>

struct Point2D {
    int32_t x;
    int32_t y;
};

constexpr int32_t screen_width  = 640;
constexpr int32_t screen_height = 480;
uint32_t*         screen_pixels = nullptr;

inline void R_PutPixel(uint32_t x, uint32_t y, uint32_t color) {
    screen_pixels[y * screen_width + x] = color;
}

int32_t R_OrientTriangle2D(Point2D* a, Point2D* b, Point2D* c) {
    return (b->x - a->x) * (c->y - a->y) - (b->y - a->y) * (c->x - a->x);
}

int32_t R_Minimum3DPoint(int32_t a, int32_t b, int32_t c) {
    int32_t result = std::numeric_limits<int32_t>::max();

    result = std::min(a, result);
    result = std::min(b, result);
    result = std::min(c, result);

    return result;
}

int32_t R_Maximum3DPoint(int32_t a, int32_t b, int32_t c) {
    int32_t result = std::numeric_limits<int32_t>::min();

    result = std::max(a, result);
    result = std::max(b, result);
    result = std::max(c, result);

    return result;
}

void R_DrawTrianglePixel(Point2D* point, int32_t w0, int32_t w1, int32_t w2) {
    R_PutPixel(point->x, point->y, 0xFFFFFFFF);
}

void R_DrawTriangle(Point2D* v0, Point2D* v1, Point2D* v2) {
    int32_t minimum_x = R_Minimum3DPoint(v0->x, v1->x, v2->x);
    int32_t minimum_y = R_Minimum3DPoint(v0->y, v1->y, v2->y);

    int32_t maximum_x = R_Maximum3DPoint(v0->x, v1->x, v2->x);
    int32_t maximum_y = R_Maximum3DPoint(v0->y, v1->y, v2->y);

    minimum_x = std::max(minimum_x, 0);
    minimum_y = std::max(minimum_y, 0);

    maximum_x = std::min(maximum_x, screen_width - 1);
    maximum_y = std::min(maximum_y, screen_height - 1);

    Point2D point {};

    for (point.y = minimum_y; point.y <= maximum_y; point.y++) {
        for (point.x = minimum_x; point.x <= maximum_x; point.x++) {
            int32_t w0 = R_OrientTriangle2D(v1, v2, &point);
            int32_t w1 = R_OrientTriangle2D(v2, v0, &point);
            int32_t w2 = R_OrientTriangle2D(v0, v1, &point);

            if (w0 >= 0 && w1 >= 0 && w2 >= 0) {
                R_DrawTrianglePixel(&point, w0, w1, w2);
            }
        }
    }
}

int main() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "Could not init SDL: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window* screen = SDL_CreateWindow("Rasterizer", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screen_width, screen_height, 0);

    if (screen == nullptr) {
        fprintf(stderr, "Could not create window\n");
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(screen, -1, SDL_RENDERER_SOFTWARE);
    if (renderer == nullptr) {
        fprintf(stderr, "Could not create renderer\n");
        return 1;
    }

    SDL_Texture* framebuffer = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, screen_width, screen_height);
    if (framebuffer == nullptr) {
        fprintf(stderr, "Could not create framebuffer\n");
        return 1;
    }

    screen_pixels = new uint32_t[screen_width * screen_height];
    if (screen_pixels == nullptr) {
        fprintf(stderr, "Could not create pixels\n");
        return 1;
    }

    Point2D v0 {
      .x = 20,
      .y = 20,
    };

    Point2D v1 {
      .x = 20,
      .y = 120,
    };

    Point2D v2 {
      .x = 120,
      .y = 120,
    };

    while (true) {
        SDL_Event event {};
        if (SDL_PollEvent(&event) == true) {
            if (event.type == SDL_QUIT) {
                break;
            } else if (event.type == SDL_KEYUP) {
                if (event.key.keysym.sym == SDLK_ESCAPE) {
                    break;
                }
            }
        }

        R_DrawTriangle(&v2, &v1, &v0);

        SDL_UpdateTexture(framebuffer, nullptr, screen_pixels, screen_width * sizeof(uint32_t));

        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, framebuffer, nullptr, nullptr);
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyWindow(screen);
    SDL_Quit();
    return 0;
}
