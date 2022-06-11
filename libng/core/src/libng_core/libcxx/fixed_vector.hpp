#pragma once

#include <third_party/eastl/eastl.hpp>

namespace libng::libcxx {

template<class T, size_t N, bool bEnableOverflow>
class fixed_vector {
public:
};

} // namespace libng::libcxx

namespace libng {

template<class T, size_t N, bool bEnableOverflow = true>
using Vector_ = eastl::fixed_vector<T, N, bEnableOverflow>;

}