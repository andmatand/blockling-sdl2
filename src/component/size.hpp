#ifndef SIZE_HPP
#define SIZE_HPP

#include <cstdint>
#include "../component.hpp"
#include "../graphics.hpp"

struct Size : Component {
    uint8_t w;
    uint8_t h;

    Size() : w(Graphics::TILE_W), h(Graphics::TILE_H) {};
};

#endif // SIZE_HPP
