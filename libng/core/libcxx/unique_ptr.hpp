#pragma once

#include <third_party/eastl/eastl.hpp>

namespace libng::libcxx {

template<typename T>
class unique_ptr {
public:
};

} // namespace libng::libcxx

namespace libng {

template<class T>
using UPtr = eastl::unique_ptr<T>;

}
