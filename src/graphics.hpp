#ifndef GRAPHICS_HPP
#define GRAPHICS_HPP

#include <SDL2/SDL.h>
#include <stdint.h>

#define FPS 30
#define GRAPHICS_SCALE 2
#define SCREEN_W 320
#define SCREEN_H 200
#define SKIN_BG_Y 64

extern int SCALED_SCREEN_W;
extern int SCALED_SCREEN_H;

extern SDL_Window* WINDOW;
extern SDL_Renderer* RENDERER;

extern SDL_Texture* SKIN_TEXTURE;
extern SDL_Rect* SKIN_BG_RECT;


uint8_t GetPixelAlpha(SDL_Surface* surface, int x, int y);

#endif // GRAPHICS_HPP
