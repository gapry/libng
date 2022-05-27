#pragma once

#include <types/function.hpp>
#include <types/number.hpp>
#include <third_party/eastl/eastl.hpp>

namespace libng {

template<class T>
using UPtr = eastl::unique_ptr<T>;

template<class T>
using Span = eastl::span<T>;

using ByteSpan = Span<const u8>;

template<class DST, class SRC>
LIBNG_INLINE Span<DST> spanCast(Span<SRC> src) {
  size_t sizeInBytes = src.size() * sizeof(SRC);
  return Span<DST>(reinterpret_cast<DST*>(src.data()), sizeInBytes / sizeof(DST));
}

template<class T, size_t N, bool bEnableOverflow = true>
using Vector_ = eastl::fixed_vector<T, N, bEnableOverflow>;

template<class T>
using Vector = eastl::vector<T>;

template<class KEY, class VALUE>
using Map = eastl::map<KEY, VALUE>;

template<class KEY, class VALUE>
using VectorMap = eastl::vector_map<KEY, VALUE>;

template<class T>
using Opt = eastl::optional<T>;

template<class T>
using StrViewT = eastl::basic_string_view<T>;

using StrViewA = StrViewT<char>;
using StrViewW = StrViewT<wchar_t>;

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

using StrView = StrViewA;
using String  = StringA;

template<size_t N>
using String_ = StringA_<N>;

inline StrView StrView_make(ByteSpan s) {
  return StrView(reinterpret_cast<const char*>(s.data()), s.size());
}

inline ByteSpan ByteSpan_make(StrView v) {
  return ByteSpan(reinterpret_cast<const u8*>(v.data()), v.size());
}

using TempString = TempStringA;

template<size_t N>
struct CharBySize;

template<>
struct CharBySize<1> {
  using Type = char;
};

template<>
struct CharBySize<2> {
  using Type = char16_t;
};

template<>
struct CharBySize<4> {
  using Type = char32_t;
};

struct WCharUtil {
  using Char = typename CharBySize<sizeof(wchar_t)>::Type;

  Char toChar(wchar_t c) {
    return static_cast<Char>(c);
  }

  wchar_t toWChar(Char c) {
    return static_cast<wchar_t>(c);
  }
};

} // namespace libng

LIBNG_INLINE
std::ostream& operator<<(std::ostream& s, const libng::StrView& v) {
  s.write(v.data(), v.size());
  return s;
}
