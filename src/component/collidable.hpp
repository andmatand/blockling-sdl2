#ifndef COLLIDABLE_HPP
#define COLLIDABLE_HPP

#include "../component.hpp"

struct Collidable : Component {
    bool isCollidable;

    Collidable() : isCollidable(true) {};
};

#endif // COLLIDABLE_HPP
