#ifndef RENDER_HPP
#define RENDER_HPP

#include <vector>
#include "../graphics.hpp"
#include "../system.hpp"
#include "../component/position.hpp"
#include "../component/size.hpp"
#include "../component/sprite.hpp"

class RenderSystem : public System {
    public:
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
