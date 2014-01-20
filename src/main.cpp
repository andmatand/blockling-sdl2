#include "main.hpp"

static void DestroySDL();
static void InitSDL();

int main(int argc, char* argv[]) {
    InitSDL();
    AssetLoader::LoadEverything();

    World world;

    // DEBUG
    Brick* brick = new Brick(0, 0);
    Brick* brick2 = new Brick(0, Graphics::TILE_H);
    world.AddEntity(brick);
    world.AddEntity(brick2);

    bool quit = false;
    while (!quit) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = true;
                break;
            }
        }

        world.Update();


        SDL_Delay(250); // TEMP: save batteries
    }

    AssetLoader::DestroyEverything();
    DestroySDL();

    return 0;
}

void InitSDL() {
    SDL_Init(SDL_INIT_VIDEO);

    Graphics::window = SDL_CreateWindow("BLOCKLING",
                                        SDL_WINDOWPOS_CENTERED,
                                        SDL_WINDOWPOS_CENTERED,
                                        Graphics::SCREEN_W,
                                        Graphics::SCREEN_H,
                                        0);

    Graphics::renderer = SDL_CreateRenderer(Graphics::window, -1,
                                            SDL_RENDERER_ACCELERATED |
                                            SDL_RENDERER_PRESENTVSYNC);

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "nearest"); // ALL the pixels!
    SDL_RenderSetLogicalSize(Graphics::renderer,
                             Graphics::SCREEN_W,
                             Graphics::SCREEN_H);

    // Hide the cursor
    SDL_ShowCursor(0);
}

void DestroySDL() {
    SDL_DestroyRenderer(Graphics::renderer);
    SDL_DestroyWindow(Graphics::window);
    SDL_Quit();
}
