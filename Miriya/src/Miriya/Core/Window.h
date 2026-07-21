#pragma once

#include <sstream>

#include "Miriya/Core/Base.h"
#include "Miriya/Events/Event.h"

namespace Miriya {

struct WindowProps
{
    std::string Title;
    uint32_t    Width;
    uint32_t    Height;

    WindowProps(const std::string& title = "Miriya Engine", unsigned int width = 1280,
                unsigned int height = 720)
        : Title(title)
        , Width(width)
        , Height(height)
    {}
};

class Window
{
public:
    using EventCallbackFn = std::function<void(Event&)>;

    virtual ~Window() {}

    // Interfaces; pure virtual
    virtual void OnUpdate() = 0;

    virtual uint32_t GetWidth() const  = 0;
    virtual uint32_t GetHeight() const = 0;

    // Window attributes
    virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
    virtual void SetVSync(bool enabled)                            = 0;
    virtual bool IsVSync() const                                   = 0;

    // return a glfw window
    // expose this as api
    // void means not necessary a glfw window
    virtual void* GetNativeWindow() const = 0;

    static Scope<Window> Create(const WindowProps& props = WindowProps());
};
}   // namespace Miriya