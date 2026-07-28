#pragma once
#include "Miriya/Core/Base.h"
#include "Miriya/Core/Application.h"

#ifdef MIR_PLATFORM_WINDOWS
// #    include <objbase.h>   // CoInitializeEx / CoUninitialize

// function returns the application
// creation is implemented in client
// extern means find in somewhere else
extern Miriya::Application* Miriya::CreateApplication(ApplicationCommandLineArgs args);

int main(int argc, char** argv)
{

    // UI 线程必须是 STA，否则 shell 文件对话框及 Explorer 扩展会报
    // RPC_E_CANTCALLOUT_ININPUTSYNCCALL。
    // CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED);

    // For test, Later move into App
    Miriya::Log::Init();
    MIR_CORE_WARN("Initialized Log");

    MIR_PROFILE_BEGIN_SESSION("Startup", "Miriya-Profile-Startup.json");
    auto app = Miriya::CreateApplication({argc, argv});
    MIR_PROFILE_END_SESSION();

    MIR_PROFILE_BEGIN_SESSION("Runtime", "Miriya-Profile-Runtime.json");
    app->Run();
    MIR_PROFILE_END_SESSION();

    MIR_PROFILE_BEGIN_SESSION("Shutdown", "Miriya-Profile-Shutdown.json");
    delete app;
    MIR_PROFILE_END_SESSION();
}

#endif