#ifndef SPRITE_HPP
#define SPRITE_HPP

#include <cstdint>

struct Sprite : Component {
    int8_t index;
    int8_t w;
    int8_t h;

    Sprite() : index(0), w(Graphics::TILE_W), h(Graphics::TILE_H) {};
};

#endif // SPRITE_HPP
