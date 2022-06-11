#pragma once

#include <libng_core/types/utility.hpp>
#include <libng_core/libcxx/string_view.hpp>
#include <third_party/eastl/eastl.hpp>

namespace libng::libcxx {

class string {
public:
};

} // namespace libng::libcxx

namespace libng {

template<class T, size_t N, bool bEnableOverflow = true>
struct StringT_Base {
  using type = typename eastl::fixed_string<T, N, bEnableOverflow>;
};

template<class T>
struct StringT_Base<T, 0, true> {
  using type = typename eastl::basic_string<T>;
};

template<class T, size_t N, bool bEnableOverflow = true>
class StringT : public StringT_Base<T, N, bEnableOverflow>::type {
  using Base = typename StringT_Base<T, N, bEnableOverflow>::type;

public:
  StringT() = default;

  StringT(const T* begin, const T* end)
    : Base(begin, end) {
  }

  StringT(StrViewT<T> view)
    : Base(view.data(), view.size()) {
  }

  StringT(StringT&& str)
    : Base(std::move(str)) {
  }

  template<class R>
  void operator=(R&& r) {
    Base::operator=(LIBNG_FORWARD(r));
  }

  void operator+=(StrViewT<T> v) {
    Base::append(v.begin(), v.end());
  }

  template<class R>
  void operator+=(const R& r) {
    Base::operator+=(r);
  }

  StrViewT<T> view() const {
    return StrViewT<T>(data(), size());
  }
};

template<size_t N, bool bEnableOverflow = true>
using StringA_ = StringT<char, N, bEnableOverflow>;

template<size_t N, bool bEnableOverflow = true>
using StringW_ = StringT<wchar_t, N, bEnableOverflow>;

using TempStringA = StringA_<220>;
using TempStringW = StringW_<220>;

using StringA = StringA_<0>;
using StringW = StringW_<0>;

using String = StringA;

template<size_t N>
using String_ = StringA_<N>;

using TempString = TempStringA;

} // namespace libng