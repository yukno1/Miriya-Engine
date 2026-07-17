#include "mirpch.h"
#include "Miriya/Core/Window.h"

#ifdef MIR_PLATFORM_WINDOWS
#    include "Platform/Windows/WindowsWindow.h"
#endif

namespace Miriya {

Scope<Window> Window::Create(const WindowProps& props)
{
#ifdef MIR_PLATFORM_WINDOWS
    return CreateScope<WindowsWindow>(props);
#else
    MIR_CORE_ASSERT(false, "Unknown platform!");
    return nullptr;
#endif
}

}   // namespace Miriya