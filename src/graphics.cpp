#include "graphics.hpp"

namespace Graphics {
    const uint16_t SCREEN_W = 640;
    const uint16_t SCREEN_H = 400;
    const uint8_t TILE_W = 16;
    const uint8_t TILE_H = 16;

    const uint8_t NUM_SPRITE_RECTS = 53;
    const uint8_t BG_SPRITE_INDEX = 52;
    const uint16_t SPRITESHEET_BG_Y = 64;
    const uint16_t SPRITESHEET_W = 256;
    const uint16_t SPRITESHEET_H = 256;

    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;

    SDL_Texture* spriteTexture = NULL;
    SDL_Rect* spriteRects = NULL;


    void AutoShrinkRect(SDL_Surface* surface, SDL_Rect* rect) {
        // Find the top
        bool finished = false;
        for (uint16_t y = rect->y; y < rect->y + rect->h; y++) {
            for (uint16_t x = rect->x; x < rect->x + rect->w; x++) {
                // If the pixel is not transparent
                if (GetPixelAlpha(surface, x, y) != 0) {
                    // Set this as the top
                    rect->h -= (y - rect->y);
                    rect->y = y;

                    finished = true;
                    break;
                }
            }

            if (finished) break;
        }

        // Find the bottom
        finished = false;
        for (uint16_t y = rect->y + rect->h - 1; y >= rect->y; y--) {
            for (uint16_t x = rect->x; x < rect->x + rect->w; x++) {
                // If the pixel is not transparent
                if (GetPixelAlpha(surface, x, y) != 0) {
                    // Adjust the height to here
                    rect->h = y - rect->y + 1;

                    finished = true;
                    break;
                }
            }

            if (finished) break;
        }

        // Find the left side
        finished = false;
        for (uint16_t x = rect->x; x < rect->w; x++) {
            for (uint16_t y = rect->y; y < rect->y + rect->h; y++) {
                // If the pixel is not transparent
                if (GetPixelAlpha(surface, x, y) != 0) {
                    // Set this as the left side
                    rect->w -= (x - rect->x);
                    rect->x = x;

                    finished = true;
                    break;
                }
            }

            if (finished) break;
        }

        // Find the right side
        finished = false;
        for (uint16_t x = rect->x + rect->w - 1; x >= rect->x; x--) {
            for (uint16_t y = rect->y; y < rect->y + rect->h; y++) {
                // If the pixel is not transparent
                if (GetPixelAlpha(surface, x, y) != 0) {
                    // Adjust the width to here
                    rect->w = x - rect->x + 1;

                    finished = true;
                    break;
                }
            }

            if (finished) break;
        }
    }

    uint8_t GetPixelAlpha(SDL_Surface* surface, int x, int y) {
        SDL_PixelFormat *pixelFormat = surface->format;
        uint32_t* pixels = (uint32_t*) surface->pixels;
        uint32_t pixel, temp;
        uint8_t alpha;

        SDL_LockSurface(surface);
        pixel = pixels[(y * surface->w) + x];
        SDL_UnlockSurface(surface);

        // Get the alpha component of the pixel color
        temp = pixel & pixelFormat->Amask;  // Isolate the alpha component
        temp = temp >> pixelFormat->Ashift; // Shift it down to 8-bit
        temp = temp << pixelFormat->Aloss;  // Expand to a full 8-bit number
        alpha = (uint8_t) temp;

        return alpha;
    }
}
