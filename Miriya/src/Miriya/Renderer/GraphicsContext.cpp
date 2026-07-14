#include "mirpch.h"
#include "Miriya/Renderer/GraphicsContext.h"

#include "Miriya/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLContext.h"

namespace Miriya {

Scope<GraphicsContext> GraphicsContext::Create(void* window)
{
    switch (Renderer::GetAPI()) {
    case RendererAPI::API::None:
        MIR_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
        return nullptr;
    case RendererAPI::API::OpenGL:
        return CreateScope<OpenGLContext>(static_cast<GLFWwindow*>(window));
    }

    MIR_CORE_ASSERT(false, "Unknown RendererAPI!");
    return nullptr;
}

}   // namespace Miriya