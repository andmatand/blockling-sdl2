#include "asset_loader.hpp"

// DEBUG
#include <iostream>

namespace AssetLoader {
    void DestroyEverything() {
        DestroySkin();
    }

    void LoadEverything() {
        std::cout << "Loading textures...";
        LoadSkin();
        std::cout << "done\n";
    }

    void AutoSizeBackgroundRect(SDL_Surface* surface, SDL_Rect* rect) {
        // Lock the surface (for subsequent GetPixel calls)
        SDL_LockSurface(surface);

        // Start with the width and height at zero
        rect->w = 0;
        rect->h = 0;

        // Detect the background height
        for (int y = surface->h - 1; y >= SKIN_BG_Y; y--) {
            if (GetPixelAlpha(surface, 0, y) != 255) {
                rect->h = y + 1 - SKIN_BG_Y;
                break;
            }
        }

        // Detect the background width
        for (int x = surface->w - 1; x > 0; x--) {
            if (GetPixelAlpha(surface, x, 0) != 255) {
                rect->w = x + 1;
                break;
            }
        }

        // Unlock the surface
        SDL_UnlockSurface(surface);
    }

    void DestroySkin() {
        SDL_DestroyTexture(SKIN_TEXTURE);
        SKIN_TEXTURE = NULL;
    }

    void LoadSkin() {
        // Load the skin into a surface
        SDL_Surface* surface = SDL_LoadBMP("res/skin/default.bmp");

        // Automatically determine the size of the background
        AutoSizeBackgroundRect(surface, SKIN_BG_RECT);

        // Create a texture from the surface
        SKIN_TEXTURE = SDL_CreateTextureFromSurface(RENDERER, surface);

        // Free the surface
        SDL_FreeSurface(surface);
    }
}
