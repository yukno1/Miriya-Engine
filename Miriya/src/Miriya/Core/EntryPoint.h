#pragma once
#include "Miriya/Core/Core.h"

#ifdef MIR_PLATFORM_WINDOWS

// function returns the application
// creation is implemented in client
// extern means find in somewhere else
//extern Miriya::Application* Miriya::CreateApplication();

int main(int argc, char** argv) {

    // For test, Later move into App
    Miriya::Log::Init();
    MIR_CORE_WARN("Initialized Log");

    MIR_PROFILE_BEGIN_SESSION("Startup", "../../Sandbox/Miriya-Profile-Startup.json");
    auto app = Miriya::CreateApplication();
    MIR_PROFILE_END_SESSION();

    MIR_PROFILE_BEGIN_SESSION("Runtime", "../../Sandbox/Miriya-Profile-Runtime.json");
    app->Run();
    MIR_PROFILE_END_SESSION();

    MIR_PROFILE_BEGIN_SESSION("Shutdown", "../../Sandbox/Miriya-Profile-Shutdown.json");
    delete app;
    MIR_PROFILE_END_SESSION();
}

#endif