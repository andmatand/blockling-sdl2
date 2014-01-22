#ifndef GRAVITY_HPP
#define GRAVITY_HPP

#include <vector>
#include "../entity.hpp"
#include "../graphics.hpp"
#include "../system.hpp"
#include "../component/position.hpp"
#include "../component/size.hpp"
#include "../component/sprite.hpp"
#include "../component/velocity.hpp"

// DEBUG
#include <iostream>

class GravitySystem : public System {
    public:
        GravitySystem();
        void AddEntity(Entity* entity);
        void Update();

    private:
        struct Node {
            Velocity* velocity;
        };

        std::vector<Node> nodes;
};

#endif // GRAVITY_HPP
