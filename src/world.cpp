#include "world.hpp"

World::World() : physicsAccumulator(0) {
    // DEBUG
    using Graphics::TILE_W;
    using Graphics::TILE_H;
    Brick* brick = new Brick(TILE_W * 9, TILE_H * 7);
    AddEntity(brick);

    for (uint16_t y = 0; y < 3; y++) {
        Block* block = new Block(TILE_W * 9, TILE_H * y);
        AddEntity(block);
    }
}

void World::AddEntity(Entity* entity) {
    gravitySystem.AddEntity(entity);
    physicsSystem.AddEntity(entity);
    renderSystem.AddEntity(entity);
}

void World::Update(uint32_t timeDelta) {
    const float PHYSICS_TIMESTEP = 20;

    physicsAccumulator += timeDelta;

    //uint16_t numSteps = 0;
    while (physicsAccumulator >= PHYSICS_TIMESTEP) {
        //numSteps++;

        gravitySystem.Update();
        physicsSystem.Update();

        physicsAccumulator -= PHYSICS_TIMESTEP;
    }
    //if (numSteps != 1) {
    //    std::cout << "steps: " << numSteps << "\n";
    //}

    renderSystem.Update();
}
