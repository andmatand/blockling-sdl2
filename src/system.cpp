#include "system.hpp"

bool System::ScreenEntity(Entity* entity) {
    // If this entity has the set of components that we operate on
    if ((entity->GetComponentMask() & componentMask) == componentMask) {
        return true;
    }
    else {
        return false;
    }
}
