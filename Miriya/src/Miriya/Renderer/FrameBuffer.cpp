#include "mirpch.h"
#include "Miriya/Renderer/Framebuffer.h"

#include "Miriya/Renderer/Renderer.h"

#include "Platform/OpenGL/OpenGLFramebuffer.h"

namespace Miriya {

Ref<Framebuffer> Framebuffer::Create(const FramebufferSpecification& spec)
{
    switch (Renderer::GetAPI()) {
    case RendererAPI::API::None:
        MIR_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
        return nullptr;
    case RendererAPI::API::OpenGL: return CreateRef<OpenGLFramebuffer>(spec);
    }

    MIR_CORE_ASSERT(false, "Unknown RendererAPI!");
    return nullptr;
}

}   // namespace Miriya