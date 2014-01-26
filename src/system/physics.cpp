#include "physics.hpp"

void PhysicsSystem::AddEntity(Entity* entity) {
    if (ScreenEntity(entity, (POSITION | SIZE | VELOCITY))) {
        Node node;
        node.position = static_cast<Position*>(entity->GetComponent(POSITION));
        node.size = static_cast<Size*>(entity->GetComponent(SIZE));
        node.velocity = static_cast<Velocity*>(entity->GetComponent(VELOCITY));

        nodes.push_back(node);
    }

    if (ScreenEntity(entity, (COLLIDABLE | POSITION | SIZE))) {
        Node c;
        c.position = static_cast<Position*>(entity->GetComponent(POSITION));
        c.size = static_cast<Size*>(entity->GetComponent(SIZE));
        
        // Get velocity as an optional components, which will be NULL if not
        // present
        c.velocity = static_cast<Velocity*>(entity->GetComponent(VELOCITY));

        collidables.push_back(c);
    }
}

// Returns the first node encountered that overlaps with the given position and
// size
PhysicsSystem::Node* PhysicsSystem::FindNode(Position position, Size size) {
    for (auto& node : nodes) {
        if (RectangleOverlap(position, size, *node.position, *node.size)) {
            return &node;
        }
    }

    return NULL;
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

bool PhysicsSystem::RectangleOverlap(Position position1, Size size1,
                                     Position position2, Size size2) {
    if (position1.x < (position2.x + size2.w) &&
        (position1.x + size1.w) > position2.x &&
        position1.y < (position2.y + size2.h) &&
        (position1.y + size1.h) > position2.y) {
        return true;
    }
    else {
        return false;
    }
}

// Return values:
//   true   Update completed
//   false  Update is postponed
bool PhysicsSystem::UpdateNodeAxis(Node* node, AXIS axis) {
    // If the node already moved
    if (node->velocity->hasMoved) {
        return true;
    }

    Position originalPosition, testPosition, previousPosition, destination;
    bool hit = false;
    bool postpone = false;
    int8_t velocity = 0;
    int8_t velocityStep = 0;

    if (axis == Y) {
        velocity = node->velocity->y;

        destination.x = node->position->x;
        destination.y = node->position->y + node->velocity->y;
    }
    else {
        velocity = node->velocity->x;

        destination.x = node->position->x + node->velocity->x;
        destination.y = node->position->y;
    }

    if (velocity > 0) {
        velocityStep = 1;
    }
    else if (velocity < 0) {
        velocityStep = -1;
    }
    else {
        return true;
    }


    testPosition.x = node->position->x;
    testPosition.y = node->position->y;
    originalPosition.x = node->position->x;
    originalPosition.y = node->position->y;

    while (testPosition.x != destination.x || testPosition.y != destination.y) {
        previousPosition.x = testPosition.x;
        previousPosition.y = testPosition.y;

        if (axis == X) {
            testPosition.x += velocityStep;
        }
        else {
            testPosition.y += velocityStep;
        }

        for (auto cn : collidables) {
            // If the collidable is not for the same entity, and the node is
            // overlapping with it
            if (!NodesAreTheSame(node, &cn) &&
                RectangleOverlap(testPosition, *node->size,
                                 *cn.position, *cn.size)) {

                // If the collidable is not movable, or it has already moved
                // this frame
                if (cn.velocity == NULL || cn.velocity->hasMoved) {
                    // Consider this a hit
                    hit = true;
                    break;
                }

                // If the collidable can move
                if (cn.velocity != NULL) {
                    // If the collidable has not been updated yet
                    if (!cn.velocity->hasUpdated) {
                        postpone = true;
                        break;
                    }

                    // If the collidable has not been pushed yet, and it is not
                    // moving
                    if (!cn.velocity->hasBeenPushed &&
                        cn.velocity->x == 0 && cn.velocity->y == 0) {
                        if (axis == X) {
                            if (velocity > 0) {
                                cn.velocity->x = (destination.x +
                                                  node->size->w) -
                                                 cn.position->x;
                            }
                            else {
                                cn.velocity->x = destination.x -
                                                 (cn.position->x + cn.size->w);
                            }

                            cn.velocity->hasUpdated = false;
                            cn.velocity->hasBeenPushed = true;
                            postpone = true;
                            break;
                        }
                    }
                }

                hit = true;
                break;
            }
        }

        if (hit || postpone) break;
    }

    if (hit) {
        // Clear the node's velocity
        if (axis == Y) {
            node->velocity->y = 0;
        }
        else {
            node->velocity->x = 0;
        }
    }

    // If the node's movement was postponed
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

        // If the node's position has changed
        if (node->position->x != originalPosition.x ||
            node->position->y != originalPosition.y) {
            node->velocity->hasMoved = true;

            if (axis == X) {
                // Apply friction
                node->velocity->x = 0;

                // Check if there is a node on top of the node's original
                // position
                Position searchPosition;
                searchPosition.x = originalPosition.x;
                searchPosition.y = originalPosition.y - 1;

                Size searchSize;
                searchSize.w = 1;
                searchSize.h = 1;

                Node* passenger = FindNode(searchPosition, searchSize);

                // If a passenger was found, and it is aligned with the node's
                // original position on the x-axis
                if (passenger != NULL &&
                    passenger->position->x == originalPosition.x) {
                    // Set the passenger's velocity to what it needs to be to
                    // move to where the node is now
                    passenger->velocity->x = node->position->x -
                                             originalPosition.x;
                    passenger->velocity->hasUpdated = false;
                }
            }
        }

        return true;
    }
}

void PhysicsSystem::UpdateNode(Node* node) {
    if (node->velocity->hasUpdated) {
        return;
    }

    if (UpdateNodeAxis(node, Y)) {
        if(UpdateNodeAxis(node, X)) {
            node->velocity->hasUpdated = true;
        }
    }
}

void PhysicsSystem::Update() {
    for (auto node : nodes) {
        node.velocity->hasUpdated = false;
        node.velocity->hasMoved = false;
        node.velocity->hasBeenPushed = false;
    }

    bool anyNodesNeedUpdate = true;
    while (anyNodesNeedUpdate) {
        anyNodesNeedUpdate = false;
        for (auto node : nodes) {
            UpdateNode(&node);

            // If this node was not updated
            if (!node.velocity->hasUpdated) {
                anyNodesNeedUpdate = true;
            }
        }
    }
}
