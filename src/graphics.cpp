#include "graphics.hpp"

int SCALED_SCREEN_W = SCREEN_W * GRAPHICS_SCALE;
int SCALED_SCREEN_H = SCREEN_H * GRAPHICS_SCALE;

SDL_Window* WINDOW = NULL;
SDL_Renderer* RENDERER = NULL;

SDL_Texture* SKIN_TEXTURE = NULL;
SDL_Rect* SKIN_BG_RECT = NULL;


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
