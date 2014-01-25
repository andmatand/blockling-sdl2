#ifndef WORLD_HPP
#define WORLD_HPP

#include <vector>
#include "entity.hpp"
#include "entity/block.hpp"
#include "entity/brick.hpp"
#include "entity/player.hpp"
#include "system.hpp"
#include "system/gravity.hpp"
#include "system/physics.hpp"
#include "system/render.hpp"

class World {
    public:
        World();
        void Update(uint32_t timeDelta);
        void AddEntity(Entity*);

    private:
        float physicsAccumulator;
        GravitySystem gravitySystem;
        PhysicsSystem physicsSystem;
        RenderSystem renderSystem;

        // DEBUG
        Velocity* playerVelocity;
};

#endif // WORLD_HPP
