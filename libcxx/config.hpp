#pragma once

#include <EASTL/span.h>
#include <EASTL/unique_ptr.h>

#include <string>
#include <vector>

namespace gnet {

template <class T>
using span = eastl::span<T>;

template <class T>
using uptr = eastl::unique_ptr<T>;

template <typename T>
using vector = std::vector<T>;

using string = std::string;

} // namespace gnet
