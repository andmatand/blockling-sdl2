#ifndef VELOCITY_HPP
#define VELOCITY_HPP

#include <cstdint>
#include "../component.hpp"

struct Velocity : Component {
    int8_t x;
    int8_t y;
    bool hasMoved;
    bool hasUpdated;
    bool hasBeenPushed;

    Velocity() : x(0), y(0), hasMoved(false), hasUpdated(false) {};
};

#endif // VELOCITY_HPP
