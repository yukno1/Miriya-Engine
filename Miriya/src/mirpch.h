#pragma once

#include "Miriya/Core/PlatformDetection.h"

#ifdef HZ_PLATFORM_WINDOWS
#    ifndef NOMINMAX
// See
// github.com/skypjack/entt/wiki/Frequently-Asked-Questions#warning-c4003-the-min-the-max-and-the-macro
#        define NOMINMAX
#    endif
#endif

#include <iostream>
#include <memory>
#include <utility>
#include <algorithm>
#include <functional>

#include <sstream>
#include <array>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>

#include "Miriya/Core/Base.h"

#include "Miriya/Core/Log.h"

#include "Miriya/Debug/Instrumentor.h"

#ifndef MIR_PLATFORM_WINDOWS
#    include <Windows.h>

#endif
