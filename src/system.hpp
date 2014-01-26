#ifndef SYSTEM_HPP
#define SYSTEM_HPP

#include <cstdint>
#include "entity.hpp"

class System {
    public:
        virtual void AddEntity(Entity* entity) = 0;
        virtual void Update() = 0;

    protected:
        static bool ScreenEntity(Entity* entity, uint32_t componentMask);
};

#endif // SYSTEM_HPP
