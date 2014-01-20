#include "brick.hpp"

Brick::Brick(int32_t x, int32_t y) {
    Position* position = new Position();
    position->x = x;
    position->y = y;
    AddComponent(POSITION, position);

    AddComponent(SIZE, new Size());

    Sprite* sprite = new Sprite();
    sprite->index = 2;
    AddComponent(SPRITE, sprite);
}
