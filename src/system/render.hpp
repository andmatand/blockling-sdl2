#ifndef RENDER_HPP
#define RENDER_HPP

#include <vector>
#include "../graphics.hpp"
#include "../system.hpp"
#include "../component/position.hpp"
#include "../component/size.hpp"
#include "../component/sprite.hpp"

// DEBUG
#include <iostream>

class RenderSystem : public System {
    public:
        RenderSystem();
        void AddEntity(Entity* entity);
        void Update();

    private:
        struct Node {
            Position* position;
            Size* size;
            Sprite* sprite;
        };

        std::vector<Node> nodes;
};

#endif // RENDER_HPP
