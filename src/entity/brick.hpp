#ifndef BRICK_HPP
#define BRICK_HPP

#include "../component_type.hpp"
#include "../component/position.hpp"
#include "../component/size.hpp"
#include "../component/sprite.hpp"
#include "../entity.hpp"

class Brick : public Entity {
    public:
        Brick(int32_t x = 0, int32_t y = 0);
};

#endif // BRICK_HPP
