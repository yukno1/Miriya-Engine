#include <Miriya.h>
#include <Miriya/Core/EntryPoint.h>

#include "EditorLayer.h"

namespace Miriya {

class MiriyaEditor : public Application
{
public:
    MiriyaEditor()
        : Application("Miriya Editor")
    {
        PushLayer(new EditorLayer());
    }

    ~MiriyaEditor() {}
};

Application* CreateApplication()
{
    return new MiriyaEditor();
}

}   // namespace Miriya