#ifndef ASSET_LOADER_HPP
#define ASSET_LOADER_HPP

#include <SDL2/SDL.h>
#include <stdint.h>
#include "graphics.hpp"

namespace AssetLoader {
    void AutoSizeBackgroundRect(SDL_Surface*, SDL_Rect*);

    void LoadEverything();
    void DestroyEverything();

    void LoadSkin();
    void DestroySkin();
}

#endif // ASSETLOADER_HPP
