#pragma once

#include "entt.hpp"

#include "Miriya/Core/Timestep.h"

namespace Miriya {

class Scene
{
public:
    Scene();
    ~Scene();

    entt::entity CreateEntity();

    // TEMP
    entt::registry& Reg() { return m_Registry; }

    void OnUpdate(Timestep ts);

private:
    entt::registry m_Registry;
};

}   // namespace Miriya