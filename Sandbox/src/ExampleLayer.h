#pragma once

#include "Miriya.h"

class ExampleLayer : public Miriya::Layer
{
public:
    ExampleLayer();
    virtual ~ExampleLayer() = default;

    virtual void OnAttach() override;
    virtual void OnDetach() override;

    void         OnUpdate(Miriya::Timestep ts) override;
    virtual void OnImGuiRender() override;
    void         OnEvent(Miriya::Event& e) override;

private:
    Miriya::ShaderLibrary            m_ShaderLibrary;
    Miriya::Ref<Miriya::Shader>      m_Shader;
    Miriya::Ref<Miriya::VertexArray> m_VertexArray;

    Miriya::Ref<Miriya::Shader>      m_FlatColorShader;
    Miriya::Ref<Miriya::VertexArray> m_SquareVA;

    Miriya::Ref<Miriya::Texture2D> m_Texture, m_ChernoLogoTexture;

    Miriya::OrthographicCameraController m_CameraController;
    glm::vec3                            m_SquareColor = {0.2f, 0.3f, 0.8f};
};