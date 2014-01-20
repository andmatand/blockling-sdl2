#ifndef WORLD_HPP
#define WORLD_HPP

#include <vector>
#include "entity.hpp"
#include "system.hpp"
#include "system/render.hpp"

class World {
    public:
        void Update();
        void AddEntity(Entity*);

    private:
        RenderSystem renderSystem;
};

#endif // WORLD_HPP
