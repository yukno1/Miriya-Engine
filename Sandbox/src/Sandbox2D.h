#pragma once

#include "Miriya.h"

class Sandbox2D : public Miriya::Layer {
public:
    Sandbox2D();
    virtual ~Sandbox2D() = default;

    void OnAttach() override;
    void OnDetach() override;

    void OnUpdate(Miriya::Timestep ts) override;
    void OnImGuiRender() override;
    void OnEvent(Miriya::Event& e) override;
private:
    Miriya::OrthographicCameraController m_CameraController;

    // Temp
    Miriya::Ref<Miriya::VertexArray> m_SquareVA;
    Miriya::Ref<Miriya::Shader> m_FlatColorShader;

    Miriya::Ref<Miriya::Texture2D> m_CheckerboardTexture;

    glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };
};


