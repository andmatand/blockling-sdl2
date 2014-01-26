#include "render.hpp"

void RenderSystem::AddEntity(Entity* entity) {
    if (!ScreenEntity(entity, (POSITION | SIZE | SPRITE))) return;

    Node node;
    node.position = static_cast<Position*>(entity->GetComponent(POSITION));
    node.size = static_cast<Size*>(entity->GetComponent(SIZE));
    node.sprite = static_cast<Sprite*>(entity->GetComponent(SPRITE));

    nodes.push_back(node);
}

void RenderSystem::Update() {
    SDL_RenderClear(Graphics::renderer);

    // DEBUG
    SDL_RenderSetScale(Graphics::renderer, 2, 2);
    for (auto node : nodes) {
        SDL_Rect destRect;
        destRect.x = node.position->x;
        destRect.y = node.position->y;
        destRect.w = node.sprite->w;
        destRect.h = node.sprite->h;

        SDL_RenderCopy(Graphics::renderer,
                       Graphics::spriteTexture,
                       &Graphics::spriteRects[node.sprite->index],
                       &destRect);
    }

    SDL_RenderPresent(Graphics::renderer);
}
