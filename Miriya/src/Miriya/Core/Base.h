#pragma once

#include <memory>

#include "Miriya/Core/PlatformDetection.h"

#ifdef MIR_DEBUG
#    if defined(MIR_PLATFORM_WINDOWS)
#        define MIR_DEBUGBREAK() __debugbreak()
#    elif defined(MIR_PLATFORM_LINUX)
#        include <signal.h>
#        define MIR_DEBUGBREAK() raise(SIGTRAP)
#    else
#        error "Platform doesn't support debugbreak yet!"
#    endif
#    define MIR_ENABLE_ASSERTS
#else
#    define MIR_DEBUGBREAK()
#endif

#define MIR_EXPAND_MACRO(x) x
#define MIR_STRINGIFY_MACRO(x) #x

#define BIT(x) (1 << x)

#define MIR_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

namespace Miriya {

template<typename T> using Scope = std::unique_ptr<T>;
template<typename T, typename... Args> constexpr Scope<T> CreateScope(Args&&... args)
{
    return std::make_unique<T>(std::forward<Args>(args)...);
}

template<typename T> using Ref = std::shared_ptr<T>;
template<typename T, typename... Args> constexpr Ref<T> CreateRef(Args&&... args)
{
    return std::make_shared<T>(std::forward<Args>(args)...);
}

}   // namespace Miriya

#include "Miriya/Core/Log.h"
#include "Miriya/Core/Assert.h"