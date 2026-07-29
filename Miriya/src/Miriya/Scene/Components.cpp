#include "mirpch.h"

#include "Components.h"
#include "ScriptableEntity.h"

namespace Miriya {

void DestroyNativeScript(NativeScriptComponent* nsc)
{
    delete nsc->Instance;
    nsc->Instance = nullptr;
}

}   // namespace Miriya