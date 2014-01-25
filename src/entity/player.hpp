#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "../component_type.hpp"
#include "../component/collidable.hpp"
#include "../component/position.hpp"
#include "../component/size.hpp"
#include "../component/sprite.hpp"
#include "../component/velocity.hpp"
#include "../entity.hpp"

class Player : public Entity {
    public:
        Player(int32_t x = 0, int32_t y = 0);
};

#endif // PLAYER_HPP
