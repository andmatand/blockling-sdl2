#ifndef ASSET_LOADER_HPP
#define ASSET_LOADER_HPP

#include <SDL2/SDL.h>
#include <stdint.h>
#include "graphics.hpp"

namespace AssetLoader {
    void LoadEverything();
    void DestroyEverything();

    void LoadSkin();
    void DestroySkin();

    void InitSpriteRects();
    void DestroySpriteRects();
}

#endif // ASSETLOADER_HPP
