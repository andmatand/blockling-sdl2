#ifndef BLOCK_HPP
#define BLOCK_HPP

#include "../component_type.hpp"
#include "../component/collidable.hpp"
#include "../component/position.hpp"
#include "../component/size.hpp"
#include "../component/sprite.hpp"
#include "../component/velocity.hpp"
#include "../entity.hpp"

class Block : public Entity {
    public:
        Block(int32_t x = 0, int32_t y = 0);
};

#endif // BLOCK_HPP
