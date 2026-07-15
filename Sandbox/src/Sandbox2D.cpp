#include "Sandbox2D.h"
#include "glm/trigonometric.hpp"
#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include "glm/gtc/type_ptr.hpp"
#include "Miriya/Renderer/Renderer2D.h"

Sandbox2D::Sandbox2D()
    : Layer("Sandbox2D")
    , m_CameraController(1280.0f / 720.0f)
{}

void Sandbox2D::OnAttach()
{
    MIR_PROFILE_FUNCTION();

    m_CheckerboardTexture =
        Miriya::Texture2D::Create("../../Sandbox/assets/textures/Checkerboard.png");
}

void Sandbox2D::OnDetach()
{
    MIR_PROFILE_FUNCTION();
}

void Sandbox2D::OnUpdate(Miriya::Timestep ts)
{
    MIR_PROFILE_FUNCTION();

    // Update
    m_CameraController.OnUpdate(ts);


    // Render
    {
        MIR_PROFILE_SCOPE("Renderer Prep");
        Miriya::RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1});
        Miriya::RenderCommand::Clear();
    }

    {
        MIR_PROFILE_SCOPE("Renderer Draw");
        Miriya::Renderer2D::BeginScene(m_CameraController.GetCamera());
        // Miriya::Renderer2D::DrawRotatedQuad({-1.0f, 0.0f}, {0.8f, 0.8f}, glm::radians(45.0f),
        // {0.8f, 0.2f, 0.3f, 1.0f});
        Miriya::Renderer2D::DrawQuad({-1.0f, 0.0f}, {0.8f, 0.8f}, {0.8f, 0.2f, 0.3f, 1.0f});
        Miriya::Renderer2D::DrawQuad({0.5f, -0.5f}, {0.5f, 0.75f}, {0.2f, 0.3f, 0.8f, 1.0f});
        // Miriya::Renderer2D::DrawQuad(
        //     {0.0f, 0.0f, -0.1f}, {10.0f, 10.0f}, m_CheckerboardTexture, 10.0f);
        Miriya::Renderer2D::DrawQuad(
            {-5.0f, -5.0f, -0.1f}, {10.0f, 10.0f}, m_CheckerboardTexture, 10.0f);
        Miriya::Renderer2D::DrawQuad(
            {-0.5f, -0.5f, 0.0f}, {1.0f, 1.0f}, m_CheckerboardTexture, 20.0f);
        Miriya::Renderer2D::EndScene();
    }

    // TODO: Shader::SetMat4, Shader::SetFloat4
    // std::dynamic_pointer_cast<Miriya::OpenGLShader>(m_FlatColorShader)->Bind();
    // std::dynamic_pointer_cast<Miriya::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat4("u_Color",
    // m_SquareColor);
}

void Sandbox2D::OnImGuiRender()
{
    MIR_PROFILE_FUNCTION();

    ImGui::Begin("Settings");
    ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));

    ImGui::End();
}

void Sandbox2D::OnEvent(Miriya::Event& e)
{
    m_CameraController.OnEvent(e);
}
