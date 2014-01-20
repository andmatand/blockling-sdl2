#ifndef GRAPHICS_HPP
#define GRAPHICS_HPP

#include <SDL2/SDL.h>
#include <cstdint>

#define GRAPHICS_SCALE 2

namespace Graphics {
    extern const uint16_t SCREEN_W;
    extern const uint16_t SCREEN_H;
    extern const uint8_t TILE_W;
    extern const uint8_t TILE_H;

    extern const uint8_t NUM_SPRITE_RECTS;
    extern const uint8_t BG_SPRITE_INDEX;
    extern const uint16_t SPRITESHEET_BG_Y;
    extern const uint16_t SPRITESHEET_W;
    extern const uint16_t SPRITESHEET_H;

    extern SDL_Window* window;
    extern SDL_Renderer* renderer;

    extern SDL_Texture* spriteTexture;
    extern SDL_Rect* spriteRects;

    void AutoShrinkRect(SDL_Surface* surface, SDL_Rect* rect);
    uint8_t GetPixelAlpha(SDL_Surface* surface, int x, int y);
}

#endif // GRAPHICS_HPP
