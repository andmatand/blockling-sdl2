#include "world.hpp"

void World::AddEntity(Entity* entity) {
    renderSystem.AddEntity(entity);
}

void World::Update() {
    renderSystem.Update();
}
