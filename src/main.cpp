#include "main.hpp"

static void DestroySDL();
static void InitSDL();

int main(int argc, char* argv[]) {
    InitSDL();
    AssetLoader::LoadEverything();

    World* world = new World();

    bool quit = false;
    uint32_t timeDelta;
    uint32_t lastTicks = SDL_GetTicks();
    uint32_t currentTicks;
    while (!quit) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    quit = true;
                    break;
                case SDL_KEYDOWN:
                    if (event.key.keysym.sym == SDLK_SPACE) {
                        delete world;
                        world = NULL;

                        world = new World();
                    }
                    break;
            }
        }

        currentTicks = SDL_GetTicks();
        timeDelta = currentTicks - lastTicks;
        lastTicks = currentTicks;

        world->Update(timeDelta);

        //SDL_Delay(50); // DEBUG: create artificial lag
    }
    delete world;
    world = NULL;

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
