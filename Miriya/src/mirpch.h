#pragma once

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

#include "Miriya/Debug/Instrumentor.h"

#ifndef MIR_PLATFORM_WINDOWS
    #include <Windows.h>

#endif

// Include core logging functionality
#include "Miriya/Core/Log.h"
