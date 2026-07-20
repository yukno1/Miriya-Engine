#include "mirpch.h"
#include "Entity.h"

namespace Miriya {

Entity::Entity(entt::entity handle, Scene* scene)
    : m_EntityHandle(handle)
    , m_Scene(scene)
{}

}   // namespace Miriya