#pragma once

#include <iostream>
#include <libng_core/types/function.hpp>
#include <third_party/eastl/eastl.hpp>

namespace libng::libcxx {

class string_view {
public:
};

} // namespace libng::libcxx

namespace libng {

template<class T>
using StrViewT = eastl::basic_string_view<T>;

using StrViewA = StrViewT<char>;
using StrViewW = StrViewT<wchar_t>;

using StrView = StrViewA;

}; // namespace libng

LIBNG_INLINE
std::ostream& operator<<(std::ostream& s, const libng::StrView& v) {
  s.write(v.data(), v.size());
  return s;
}
