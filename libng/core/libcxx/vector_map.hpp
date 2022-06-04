#pragma once

#include <third_party/eastl/eastl.hpp>

namespace libng::libcxx {

class vector_map {
public:
};

} // namespace libng::libcxx

namespace libng {

template<class KEY, class VALUE>
using VectorMap = eastl::vector_map<KEY, VALUE>;

}