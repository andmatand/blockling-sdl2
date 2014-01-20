#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <cstdint>
#include <unordered_map>
#include "component.hpp"
#include "component_type.hpp"

class Entity {
    public:
        uint32_t GetComponentMask();
        void AddComponent(COMPONENT_TYPE, Component*);
        Component* GetComponent(COMPONENT_TYPE);

    protected:
        Entity();

    private:
        uint32_t componentMask;
        std::unordered_map<uint32_t, Component*> components;
};

#endif // ENTITY_HPP
