#include "system.hpp"

bool System::ScreenEntity(Entity* entity, uint32_t componentMask) {
    // If this entity has the set of components specified in the mask
    if ((entity->GetComponentMask() & componentMask) == componentMask) {
        return true;
    }
    else {
        return false;
    }
}
