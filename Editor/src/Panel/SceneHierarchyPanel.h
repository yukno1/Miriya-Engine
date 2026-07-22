#pragma once

#include "Miriya/Core/Base.h"
#include "Miriya/Core/Log.h"
#include "Miriya/Scene/Scene.h"
#include "Miriya/Scene/Entity.h"

namespace Miriya {

class SceneHierarchyPanel
{
public:
    SceneHierarchyPanel() = default;
    SceneHierarchyPanel(const Ref<Scene>& scene);

    void SetContext(const Ref<Scene>& scene);

    void OnImGuiRender();

private:
    void DrawEntityNode(Entity entity);
    void DrawComponents(Entity entity);

private:
    Ref<Scene> m_Context;
    Entity     m_SelectionContext;
};

}   // namespace Miriya