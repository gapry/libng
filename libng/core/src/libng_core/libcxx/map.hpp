#pragma once

#include <third_party/eastl/eastl.hpp>

namespace libng::libcxx {

template<class KEY, class VALUE>
class map {
public:
};

} // namespace libng::libcxx

namespace libng {

template<class KEY, class VALUE>
using Map = eastl::map<KEY, VALUE>;

}