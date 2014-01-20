#include "asset_loader.hpp"

// DEBUG
#include <iostream>

namespace AssetLoader {
    void DestroyEverything() {
        DestroySpriteRects();
        DestroySkin();
    }

    void DestroySkin() {
        SDL_DestroyTexture(Graphics::spriteTexture);
        Graphics::spriteTexture = NULL;
    }

    void DestroySpriteRects() {
        delete [] Graphics::spriteRects;
        Graphics::spriteRects = NULL;
    }

    void InitSpriteRects(SDL_Surface* surface) {
        using Graphics::NUM_SPRITE_RECTS;
        using Graphics::SPRITESHEET_W;
        using Graphics::TILE_W;
        using Graphics::TILE_H;
        using Graphics::AutoShrinkRect;
        using Graphics::spriteRects;

        spriteRects = new SDL_Rect[NUM_SPRITE_RECTS];

        uint16_t x = 0;
        uint16_t y = 0;
        for (uint8_t i = 0; i < NUM_SPRITE_RECTS; i++) {
            spriteRects[i].x = x;
            spriteRects[i].y = y;
            spriteRects[i].w = TILE_W;
            spriteRects[i].h = TILE_H;

            // Automatically shrink the rect to the actual size of the sprite
            AutoShrinkRect(surface, &spriteRects[i]);

            x += TILE_W;
            if (x >= SPRITESHEET_W) {
                x = 0;
                y += TILE_H;
            }
        }
    }

    void LoadEverything() {
        std::cout << "Loading textures...";
        LoadSkin();
        std::cout << "done\n";
    }

    void LoadSkin() {
        using Graphics::BG_SPRITE_INDEX;
        using Graphics::SPRITESHEET_BG_Y;
        using Graphics::SPRITESHEET_W;
        using Graphics::SPRITESHEET_H;
        using Graphics::AutoShrinkRect;
        using Graphics::renderer;
        using Graphics::spriteRects;
        using Graphics::spriteTexture;

        DestroySkin();

        // Load the skin into a surface
        SDL_Surface* surface = SDL_LoadBMP("asset/skin/default.bmp");

        if (spriteRects == NULL) {
            InitSpriteRects(surface);
        }

        spriteRects[BG_SPRITE_INDEX].x = 0;
        spriteRects[BG_SPRITE_INDEX].y = SPRITESHEET_BG_Y;
        spriteRects[BG_SPRITE_INDEX].w = SPRITESHEET_W;
        spriteRects[BG_SPRITE_INDEX].h = SPRITESHEET_H - SPRITESHEET_BG_Y;

        // Automatically determine the size of the background
        AutoShrinkRect(surface, &spriteRects[BG_SPRITE_INDEX]);

        // Create a texture from the surface
        spriteTexture = SDL_CreateTextureFromSurface(renderer, surface);

        // Free the surface
        SDL_FreeSurface(surface);
    }
}
