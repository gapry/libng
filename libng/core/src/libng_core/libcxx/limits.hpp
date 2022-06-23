#pragma once

#include <third_party/eastl/eastl.hpp>

namespace libng::libcxx {

template<class T>
class numeric_limits {
public:
};

} // namespace libng::libcxx

namespace libng {

template<class T>
using numeric_limits = eastl::numeric_limits<T>;

}