#include "mirpch.h"
#include "Miriya/Renderer/Renderer.h"
#include "Miriya/Renderer/Renderer2D.h"


namespace Miriya {

Scope<Renderer::SceneData> Renderer::s_SceneData = CreateScope<Renderer::SceneData>();

void Renderer::Init()
{
    MIR_PROFILE_FUNCTION();

    RenderCommand::Init();
    Renderer2D::Init();
}

void Renderer::Shutdown()
{
    Renderer2D::Shutdown();
}

void Renderer::OnWindowResize(uint32_t width, uint32_t height)
{
    RenderCommand::SetViewport(0, 0, width, height);
}

// make sure shader gets right uniforms
// environment map; cube map; camera; light; material; model; etc
void Renderer::BeginScene(OrthographicCamera& camera)
{
    s_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
}

void Renderer::EndScene() {}

// submit into render queue
void Renderer::Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray,
                      const glm::mat4& transform)
{
    shader->Bind();
    shader->SetMat4("u_ViewProjection", s_SceneData->ViewProjectionMatrix);
    shader->SetMat4("u_Transform", transform);

    vertexArray->Bind();
    // just render command; can't do multiple things
    RenderCommand::DrawIndexed(vertexArray);
}
}   // namespace Miriya
