#ifndef POSITION_HPP
#define POSITION_HPP

#include <cstdint>
#include "../component.hpp"

struct Position : Component {
    int32_t x;
    int32_t y;

    Position() : x(0), y(0) {};
};

#endif // POSITION_HPP
