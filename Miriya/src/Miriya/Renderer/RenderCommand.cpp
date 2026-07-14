#include "mirpch.h"
#include "Miriya/Renderer/RenderCommand.h"

namespace Miriya {

// future dynamically setting renderer API
Scope<RendererAPI> RenderCommand::s_RendererAPI = RendererAPI::Create();
}   // namespace Miriya