#ifndef VELOCITY_HPP
#define VELOCITY_HPP

#include <cstdint>
#include "../component.hpp"

struct Velocity : Component {
    int8_t x;
    int8_t y;
    bool hasMovedThisFrame;

    Velocity() : x(0), y(0), hasMovedThisFrame(false) {};
};

#endif // VELOCITY_HPP
