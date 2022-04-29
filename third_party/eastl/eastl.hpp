#pragma once

#include <iostream>
#include <iterator>
#include <string_view>

#include <fmt/core.h>
#include <fmt/format.h>

#include <EASTL/vector.h>
#include <EASTL/fixed_vector.h>
#include <EASTL/string.h>
#include <EASTL/fixed_string.h>
#include <EASTL/string_view.h>
#include <EASTL/span.h>

#include <EASTL/optional.h>

#include <EASTL/map.h>
#include <EASTL/hash_map.h>
#include <EASTL/vector_map.h>
#include <EASTL/string_map.h>

#include <EASTL/unique_ptr.h>
#include <EASTL/shared_ptr.h>
#include <EASTL/weak_ptr.h>

#include <types/function.hpp>
#include <platform/os.hpp>

#if !EASTL_DLL

#pragma warning(push)
#pragma warning(disable : 4100)

LIBNG_INLINE auto operator new[](size_t size,          //
                                 char const* p_name,   //
                                 int flags,            //
                                 unsigned debug_flags, //
                                 char const* file,     //
                                 int line) -> void* {  //
  return malloc(size);
}

LIBNG_INLINE auto operator new[](size_t size,             //
                                 size_t alignment,        //
                                 size_t alignment_offset, //
                                 char const* p_name,      //
                                 int flags,               //
                                 unsigned debug_flags,    //
                                 char const* file,        //
                                 int line) -> void* {     //
#if LIBNG_OS_WINDOWS
  return _aligned_malloc(size, alignment);
#else
  return std::aligned_alloc(alignment, size);
#endif
}

#pragma warning(pop)

#endif

namespace libng {

template<class T>
using UPtr = eastl::unique_ptr<T>;

template<class T>
using Span = eastl::span<T>;

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
class StringT : public eastl::fixed_string<T, N, bEnableOverflow> {
  using Base = eastl::fixed_string<T, N, bEnableOverflow>;

public:
  StringT() = default;

  StringT(StrViewT<T> view)
    : Base(view.data(), view.size()) {
  }
  StringT(StringT&& str)
    : Base(std::move(str)) {
  }

  template<class R>
  void operator=(R&& r) {
    Base::operator=(SGE_FORWARD(r));
  }
};

using StringA = eastl::basic_string<char>;
using StringW = eastl::basic_string<wchar_t>;

template<size_t N, bool bEnableOverflow = true>
using StringA_ = StringT<char, N, bEnableOverflow>;

template<size_t N, bool bEnableOverflow = true>
using StringW_ = StringT<wchar_t, N, bEnableOverflow>;

using TempStringA = StringA_<220>;
using TempStringW = StringW_<220>;

using StrView = StrViewA;
using String  = StringA;

template<size_t N>
using String_ = StringA_<N>;

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