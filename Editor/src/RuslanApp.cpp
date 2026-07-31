#include <Miriya.h>
#include <Miriya/Core/EntryPoint.h>

#include "EditorLayer.h"

namespace Miriya {

class Ruslan : public Application
{
public:
    Ruslan(const ApplicationSpecification& spec)
        : Application(spec)
    {
        PushLayer(new EditorLayer());
    }
};

Application* CreateApplication(ApplicationCommandLineArgs args)
{
    ApplicationSpecification spec;
    spec.Name            = "Ruslan";
    spec.CommandLineArgs = args;

    return new Ruslan(spec);
}

}   // namespace Miriya