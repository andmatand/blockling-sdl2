#include "main.hpp"

static void DestroySDL();
static void InitSDL();

int main(int argc, char* argv[]) {
    InitSDL();
    AssetLoader::LoadEverything();

    AssetLoader::DestroyEverything();
    DestroySDL();

    return 0;
}

void InitSDL() {
    SDL_Init(SDL_INIT_VIDEO);

    WINDOW = SDL_CreateWindow("BLOCKLING",
                              SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED,
                              SCALED_SCREEN_W,
                              SCALED_SCREEN_H,
                              0);

    RENDERER = SDL_CreateRenderer(WINDOW, -1,
                                  SDL_RENDERER_ACCELERATED |
                                  SDL_RENDERER_PRESENTVSYNC);

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "nearest"); // ALL the pixels!
    SDL_RenderSetLogicalSize(RENDERER, SCALED_SCREEN_W, SCALED_SCREEN_H);

    // Hide the cursor
    SDL_ShowCursor(0);
}

void DestroySDL() {
    SDL_DestroyRenderer(RENDERER);
    SDL_DestroyWindow(WINDOW);
    SDL_Quit();
}
