#include <Miriya.h>
#include <Miriya/Core/EntryPoint.h>

#include "Sandbox2D.h"
#include "ExampleLayer.h"


class Sandbox : public Miriya::Application
{
public:
    Sandbox(const Miriya::ApplicationSpecification& specification)
        : Miriya::Application(specification)
    {
        // PushLayer(new ExampleLayer());
        PushLayer(new Sandbox2D());
    }

    ~Sandbox() {}
};


Miriya::Application* Miriya::CreateApplication(ApplicationCommandLineArgs args)
{
    ApplicationSpecification spec;
    spec.Name             = "Sandbox";
    spec.WorkingDirectory = "../Editor";
    spec.CommandLineArgs  = args;

    return new Sandbox(spec);
}
