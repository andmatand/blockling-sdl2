#include "player.hpp"

Player::Player(int32_t x, int32_t y) {
    AddComponent(COLLIDABLE, new Collidable());

    Position* position = new Position();
    position->x = x;
    position->y = y;
    AddComponent(POSITION, position);

    AddComponent(SIZE, new Size());

    Sprite* sprite = new Sprite();
    sprite->index = 27;
    sprite->h = Graphics::TILE_H - 2;
    AddComponent(SPRITE, sprite);

    AddComponent(VELOCITY, new Velocity());
}
