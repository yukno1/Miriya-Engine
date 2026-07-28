#include <Miriya.h>
#include <Miriya/Core/EntryPoint.h>

#include "EditorLayer.h"

namespace Miriya {

class Ruslan : public Application
{
public:
    Ruslan(ApplicationCommandLineArgs args)
        : Application("Ruslan", args)
    {
        PushLayer(new EditorLayer());
    }

    ~Ruslan() {}
};

Application* CreateApplication(ApplicationCommandLineArgs args)
{
    return new Ruslan(args);
}

}   // namespace Miriya