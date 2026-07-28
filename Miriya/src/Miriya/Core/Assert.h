#pragma once

#include "Miriya/Core/Base.h"
#include "Miriya/Core/Log.h"
#include <filesystem>

#ifdef MIR_ENABLE_ASSERTS

// Alteratively we could use the same "default" message for both "WITH_MSG" and "NO_MSG" and
// provide support for custom formatting by concatenating the formatting string instead of having
// the format inside the default message
#    define MIR_INTERNAL_ASSERT_IMPL(type, check, msg, ...) \
        {                                                   \
            if (!(check)) {                                 \
                MIR##type##ERROR(msg, __VA_ARGS__);         \
                MIR_DEBUGBREAK();                           \
            }                                               \
        }
#    define MIR_INTERNAL_ASSERT_WITH_MSG(type, check, ...) \
        MIR_INTERNAL_ASSERT_IMPL(type, check, "Assertion failed: {0}", __VA_ARGS__)
#    define MIR_INTERNAL_ASSERT_NO_MSG(type, check)                                   \
        MIR_INTERNAL_ASSERT_IMPL(type,                                                \
                                 check,                                               \
                                 "Assertion '{0}' failed at {1}:{2}",                 \
                                 MIR_STRINGIFY_MACRO(check),                          \
                                 std::filesystem::path(__FILE__).filename().string(), \
                                 __LINE__)

#    define MIR_INTERNAL_ASSERT_GET_MACRO_NAME(arg1, arg2, macro, ...) macro
#    define MIR_INTERNAL_ASSERT_GET_MACRO(...)               \
        MIR_EXPAND_MACRO(MIR_INTERNAL_ASSERT_GET_MACRO_NAME( \
            __VA_ARGS__, MIR_INTERNAL_ASSERT_WITH_MSG, MIR_INTERNAL_ASSERT_NO_MSG))

// Currently accepts at least the condition and one additional parameter (the message) being
// optional
#    define MIR_ASSERT(...) \
        MIR_EXPAND_MACRO(MIR_INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__)(_, __VA_ARGS__))
#    define MIR_CORE_ASSERT(...) \
        MIR_EXPAND_MACRO(MIR_INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__)(_CORE_, __VA_ARGS__))
#else
#    define MIR_ASSERT(...)
#    define MIR_CORE_ASSERT(...)
#endif