#include "Sandbox2D.h"
#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include "glm/gtc/type_ptr.hpp"

#include "Platform/OpenGL/OpenGLShader.h"

Sandbox2D::Sandbox2D() : Layer("Sandbox2D"), m_CameraController(1280.0f / 720.0f) {
}

void Sandbox2D::OnAttach() {
    m_SquareVA = Miriya::VertexArray::Create();

    float squareVertices[3 * 4] = {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.5f,  0.5f, 0.0f,
        -0.5f,  0.5f, 0.0f
    };

    Miriya::Ref<Miriya::VertexBuffer> squareVB;
    squareVB.reset(Miriya::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
    squareVB->SetLayout({
        { Miriya::ShaderDataType::Float3, "a_Position" }
    });
    m_SquareVA->AddVertexBuffer(squareVB);

    uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
    Miriya::Ref<Miriya::IndexBuffer> squareIB;
    squareIB.reset(Miriya::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
    m_SquareVA->SetIndexBuffer(squareIB);

    m_FlatColorShader = Miriya::Shader::Create("../../Sandbox/assets/shaders/FlatColor.glsl");
}

void Sandbox2D::OnDetach() {
}

void Sandbox2D::OnUpdate(Miriya::Timestep ts) {
    // Update
    m_CameraController.OnUpdate(ts);

    // Render
    Miriya::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
    Miriya::RenderCommand::Clear();

    Miriya::Renderer::BeginScene(m_CameraController.GetCamera());

    std::dynamic_pointer_cast<Miriya::OpenGLShader>(m_FlatColorShader)->Bind();
    std::dynamic_pointer_cast<Miriya::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat4("u_Color", m_SquareColor);

    Miriya::Renderer::Submit(m_FlatColorShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

    Miriya::Renderer::EndScene();
}

void Sandbox2D::OnImGuiRender() {
    ImGui::Begin("Settings");
    ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
    ImGui::End();
}

void Sandbox2D::OnEvent(Miriya::Event &e) {
    m_CameraController.OnEvent(e);
}
