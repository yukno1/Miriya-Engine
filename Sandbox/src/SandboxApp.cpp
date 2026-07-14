#include <Miriya.h>
#include <Miriya/Core/EntryPoint.h>

#include "Sandbox2D.h"
#include "ExampleLayer.h"


class Sandbox : public Miriya::Application
{
public:
    Sandbox()
    {
        // PushLayer(new ExampleLayer());
        PushLayer(new Sandbox2D());
    }

    ~Sandbox() {}
};


Miriya::Application* Miriya::CreateApplication()
{
    return new Sandbox();
}
