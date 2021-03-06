#pragma once

#include <libng_core/libng_common.hpp>
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

LIBNG_INLINE StrView StrView_c_str(const char* s) {
  return s ? StrView(s, strlen(s)) : StrView();
}

}; // namespace libng

LIBNG_INLINE
std::ostream& operator<<(std::ostream& s, const libng::StrView& v) {
  s.write(v.data(), v.size());
  return s;
}
