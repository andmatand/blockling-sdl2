#include "world.hpp"

World::World() : physicsAccumulator(0) {
    // DEBUG: Set up a physics test scenario
    using Graphics::TILE_W;
    using Graphics::TILE_H;

    for (uint16_t x = 7; x < 15; x++) {
        Brick* brick = new Brick(TILE_W * x, TILE_H * 8);
        AddEntity(brick);
        delete brick;
    }

    for (uint16_t x = 7; x < 15; x++) {
        Block* block = new Block(TILE_W * x, TILE_H * 7);
        AddEntity(block);
        delete block;
    }

    for (uint16_t y = 0; y < 3; y++) {
        Block* block = new Block(TILE_W * 10, TILE_H * y);
        AddEntity(block);
        delete block;
    }

    for (uint16_t y = 0; y < 3; y++) {
        Block* block = new Block(TILE_W * 11, TILE_H * y);
        AddEntity(block);
        delete block;
    }

    Block* block = new Block(TILE_W * 7, TILE_H * 6);
    Velocity* velocity = static_cast<Velocity*>(block->GetComponent(VELOCITY));
    velocity->x = 2;
    AddEntity(block);
    delete block;
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
