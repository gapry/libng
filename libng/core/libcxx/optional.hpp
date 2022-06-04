#pragma once

#include <third_party/eastl/eastl.hpp>

namespace libng::libcxx {

template<typename T>
class optional {
public:
};

} // namespace libng::libcxx

namespace libng {

template<class T>
using Opt = eastl::optional<T>;

}