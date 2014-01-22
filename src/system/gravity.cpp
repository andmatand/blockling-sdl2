#include "gravity.hpp"

GravitySystem::GravitySystem() {
    componentMask = VELOCITY;
};

void GravitySystem::AddEntity(Entity* entity) {
    if (!ScreenEntity(entity)) return;

    Node node;
    node.velocity = static_cast<Velocity*>(entity->GetComponent(VELOCITY));

    nodes.push_back(node);
}

void GravitySystem::Update() {
    for (auto node : nodes) {
        node.velocity->y += 1;

        // Enforce a maximum velocity
        if (node.velocity->y > Graphics::TILE_H) {
            node.velocity->y = Graphics::TILE_H;
        }
    }
}
