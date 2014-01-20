#ifndef SYSTEM_HPP
#define SYSTEM_HPP

#include <cstdint>
#include "entity.hpp"

class System {
    public:
        virtual void AddEntity(Entity* entity) = 0;
        bool ScreenEntity(Entity* entity);
        virtual void Update() = 0;

    protected:
        uint32_t componentMask;
};

#endif // SYSTEM_HPP
