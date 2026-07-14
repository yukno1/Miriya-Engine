#pragma once

#include "Miriya/Core/Core.h"

#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace Miriya {
class Log
{
public:
    static void Init();

    inline static Ref<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
    inline static Ref<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

private:
    static Ref<spdlog::logger> s_CoreLogger;
    static Ref<spdlog::logger> s_ClientLogger;
};
}   // namespace Miriya

// Core log macros
#define MIR_CORE_ERROR(...) ::Miriya::Log::GetCoreLogger()->error(__VA_ARGS__)
#define MIR_CORE_WARN(...) ::Miriya::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define MIR_CORE_INFO(...) ::Miriya::Log::GetCoreLogger()->info(__VA_ARGS__)
#define MIR_CORE_TRACE(...) ::Miriya::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define MIR_CORE_FATAL(...) ::Miriya::Log::GetCoreLogger()->fatal(__VA_ARGS__)

// Client log macros
#define MIR_ERROR(...) ::Miriya::Log::GetClientLogger()->error(__VA_ARGS__)
#define MIR_WARN(...) ::Miriya::Log::GetClientLogger()->warn(__VA_ARGS__)
#define MIR_INFO(...) ::Miriya::Log::GetClientLogger()->info(__VA_ARGS__)
#define MIR_TRACE(...) ::Miriya::Log::GetClientLogger()->trace(__VA_ARGS__)
#define MIR_FATAL(...) ::Miriya::Log::GetClientLogger()->fatal(__VA_ARGS__)