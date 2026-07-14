#include "mirpch.h"
#include "Miriya/Renderer/Buffer.h"
#include "Platform/OpenGL/OpenGLBuffer.h"

#include "Miriya/Renderer/Renderer.h"
#include "Miriya/Core/Core.h"

namespace Miriya {
Ref<VertexBuffer> VertexBuffer::Create(float* vertices, uint32_t size)
{
    switch (Renderer::GetAPI()) {
    case RendererAPI::API::None:
        MIR_CORE_ASSERT(false, "RendererAPI::None is not supported!");
        return nullptr;
    case RendererAPI::API::OpenGL: return CreateRef<OpenGLVertexBuffer>(vertices, size);
    }
    MIR_CORE_ASSERT(false, "Unknown RendererAPI!");
    return nullptr;
}

Ref<IndexBuffer> IndexBuffer::Create(uint32_t* indices, uint32_t count)
{
    switch (Renderer::GetAPI()) {
    case RendererAPI::API::None:
        MIR_CORE_ASSERT(false, "RendererAPI::None is not supported!");
        return nullptr;
    case RendererAPI::API::OpenGL: return CreateRef<OpenGLIndexBuffer>(indices, count);
    }
    MIR_CORE_ASSERT(false, "Unknown RendererAPI!");
    return nullptr;
}
}   // namespace Miriya
