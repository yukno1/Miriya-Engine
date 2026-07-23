#pragma once

#include "Miriya/Core/Layer.h"
#include "Miriya/Events/MouseEvent.h"
#include "Miriya/Events/KeyEvent.h"
#include "Miriya/Events/ApplicationEvent.h"

namespace Miriya {

class ImGuiLayer : public Layer
{
public:
    ImGuiLayer();
    ~ImGuiLayer();

    void OnAttach() override;
    void OnDetach() override;
    void OnEvent(Event& e) override;

    // Enable layer to imgui rendering independently
    // begin a new window
    void Begin();
    void End();

    void BlockEvents(bool block) { m_BlockEvents = block; }

    void SetDarkThemeColors();

private:
    bool m_BlockEvents = true;

    float m_Time = 0.0f;
};
}   // namespace Miriya
