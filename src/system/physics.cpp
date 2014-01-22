#include "physics.hpp"

PhysicsSystem::PhysicsSystem() {
    componentMask = POSITION | SIZE | VELOCITY;
    collidableMask = COLLIDABLE | POSITION | SIZE;
};

void PhysicsSystem::AddEntity(Entity* entity) {
    if (ScreenEntity(entity)) {
        Node node;
        node.position = static_cast<Position*>(entity->GetComponent(POSITION));
        node.size = static_cast<Size*>(entity->GetComponent(SIZE));
        node.velocity = static_cast<Velocity*>(entity->GetComponent(VELOCITY));

        nodes.push_back(node);
    }

    if ((entity->GetComponentMask() & collidableMask) == collidableMask) {
        Node c;
        c.position = static_cast<Position*>(entity->GetComponent(POSITION));
        c.size = static_cast<Size*>(entity->GetComponent(SIZE));
        
        // Get velocity as an optional components, which will be NULL if not
        // present
        c.velocity = static_cast<Velocity*>(entity->GetComponent(VELOCITY));

        collidables.push_back(c);
    }
}

bool PhysicsSystem::NodeNeedsToMove(Node* node) {
    if (node->velocity != NULL) {
        if (node->velocity->x != 0 || node->velocity->y != 0 ) {
            return true;
        }
    }

    return false;
}

bool PhysicsSystem::NodesAreTheSame(Node* node1, Node* node2) {
    // This is a cheap way to check if the node is the same, without needing an
    // actual reference to the original entity
    if (node1->position->x == node2->position->x &&
        node1->position->y == node2->position->y) {
        return true;
    }
    else {
        return false;
    }
}

bool PhysicsSystem::RectangleOverlap(Position* position1, Size* size1,
                                     Position* position2, Size* size2) {
    if (position1->x < (position2->x + size2->w) &&
        (position1->x + size1->w) > position2->x &&
        position1->y < (position2->y + size2->h) &&
        (position1->y + size1->h) > position2->y) {
        return true;
    }
    else {
        return false;
    }
}

bool PhysicsSystem::UpdateNode(Node* node) {
    // If this node doesn't need to move, or it has already moved this frame
    if (!NodeNeedsToMove(node) || node->velocity->hasMovedThisFrame) {
        return true;
    }

    enum AXIS { X, Y };

    Position testPosition, previousPosition, destination;
    bool hit = false;
    bool postpone = false;
    int8_t velocity = 0;
    int8_t velocityStep = 0;
    AXIS velocityAxis;

    // Only allow velocity on one axis at a time
    if (node->velocity->x != 0) {
        velocity = node->velocity->x;
        node->velocity->y = 0;
        velocityAxis = X;
    }
    else if (node->velocity->y != 0) {
        velocity = node->velocity->y;
        node->velocity->x = 0;
        velocityAxis = Y;
    }

    if (velocity > 0) {
        velocityStep = 1;
    }
    else {
        velocityStep = -1;
    }

    destination.x = node->position->x + node->velocity->x;
    destination.y = node->position->y + node->velocity->y;

    testPosition.x = node->position->x;
    testPosition.y = node->position->y;

    //std::cout << "\ny: " << node->position->y << "\n";
    //std::cout << "dest y: " << destination.y << "\n";

    while (testPosition.x != destination.x || testPosition.y != destination.y) {
        previousPosition.x = testPosition.x;
        previousPosition.y = testPosition.y;

        if (velocityAxis == X) {
            testPosition.x += velocityStep;
        }
        else {
            testPosition.y += velocityStep;
        }

        for (auto cn : collidables) {
            // If the collidable is not for the same entity, and the node is
            // overlapping with it
            if (!NodesAreTheSame(node, &cn) &&
                RectangleOverlap(&testPosition, node->size,
                                 cn.position, cn.size)) {
                // If the collidable is not movable, or it has already moved
                // this frame
                if (cn.velocity == NULL || cn.velocity->hasMovedThisFrame) {
                    // Consider this a hit
                    //std::cout << "hit\n";
                    hit = true;
                    break;
                }
                else {
                    // Postpone the node's movement until after the collidable
                    // has moved
                    postpone = true;
                    //std::cout << "postponed\n";
                    break;
                }

                // If the collidable can move, and it hasn't already moved
                if (cn.velocity != NULL && !cn.velocity->hasMovedThisFrame) {
                    // Try to push the collidable out of the way

                    //if (velocityAxis == X) {
                    //}
                    //else {
                    //    cn.velocity->x;
                    //}
                }
            }
        }

        if (hit || postpone) break;
    }

    if (hit) {
        // Clear the node's velocity
        node->velocity->x = 0;
        node->velocity->y = 0;
    }

    // If the node's movement was not postponed
    if (postpone) {
        return false;
    }
    else {
        if (hit) {
            // Move the node to the farthest non-colliding position
            node->position->x = previousPosition.x;
            node->position->y = previousPosition.y;
        }
        else {
            // Move the node to the destination position
            node->position->x = destination.x;
            node->position->y = destination.y;
        }

        node->velocity->hasMovedThisFrame = true;

        return true;
    }
}

void PhysicsSystem::Update() {
    for (auto node : nodes) {
        node.velocity->hasMovedThisFrame = false;
    }

    bool anyNodesNeedToMove = true;
    while (anyNodesNeedToMove) {
        anyNodesNeedToMove = false;
        for (auto node : nodes) {
            bool wasUpdated = UpdateNode(&node);

            //if (!node.velocity->hasMovedThisFrame) {
            if (!wasUpdated) {
                anyNodesNeedToMove = true;
            }
        }
    }
}
