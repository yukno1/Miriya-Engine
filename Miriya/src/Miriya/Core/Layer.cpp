#include "mirpch.h"
#include "Miriya/Core/Layer.h"

namespace Miriya {

Layer::Layer(const std::string& debugName)
    : m_DebugName(debugName)
{}

Layer::~Layer() {}
}   // namespace Miriya