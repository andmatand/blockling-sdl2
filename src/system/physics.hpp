#ifndef PHYSICS_HPP
#define PHYSICS_HPP

#include <vector>
#include "../entity.hpp"
#include "../graphics.hpp"
#include "../system.hpp"
#include "../component_type.hpp"
#include "../component/collidable.hpp"
#include "../component/position.hpp"
#include "../component/size.hpp"
#include "../component/velocity.hpp"

// DEBUG
#include <iostream>

class PhysicsSystem : public System {
    public:
        PhysicsSystem();
        void AddEntity(Entity* entity);
        void Update();

    private:
        struct Node {
            Position* position;
            Size* size;
            Velocity* velocity;

            Node() : position(NULL), size(NULL), velocity(NULL) {};
        };

        uint32_t collidableMask;
        std::vector<Node> nodes;
        std::vector<Node> collidables;

        static bool RectangleOverlap(Position*, Size*, Position*, Size*);
        static bool NodesAreTheSame(Node*, Node*);
        static bool NodeNeedsToMove(Node*);
        bool UpdateNode(Node* node);
};

#endif // PHYSICS_HPP