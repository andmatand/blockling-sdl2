#include "entity.hpp"

Entity::Entity() : componentMask(0) {}

void Entity::AddComponent(COMPONENT_TYPE componentType, Component* component) {
    components[componentType] = component;

    // Enable this component type bit in our mask
    componentMask = componentMask | componentType;
}

Component* Entity::GetComponent(COMPONENT_TYPE componentType) {
    // Return the component with the specified type (if it exists; otherwise
    // return NULL);
    try {
        return components.at(componentType);
    }
    catch (std::out_of_range& e) {
        return NULL;
    }
}

uint32_t Entity::GetComponentMask() {
    return componentMask;
}
