#pragma once

#include <platform/compiler.hpp>
#include <types/utility.hpp>
#include <libcxx/util.hpp>

#include <iterator>
#include <fmt/format.h>

#if LIBNG_COMPILER_VC
#if _DEBUG
#pragma comment(lib, "fmtd.lib")
#else
#pragma comment(lib, "fmt.lib")
#endif
#endif

#define LIBNG_FORMATTER(T)                              \
  template<>                                            \
  struct fmt::formatter<T> {                            \
    auto parse(fmt::format_parse_context& ctx) {        \
      return ctx.begin();                               \
    }                                                   \
    auto format(const T& v, fmt::format_context& ctx) { \
      return v.onFormat(ctx);                           \
    }                                                   \
  };

namespace libng {

template<class... ARGS>
LIBNG_INLINE void FmtTo(TempString& outStr, ARGS&&... args) {
  fmt::format_to(std::back_inserter(outStr), LIBNG_FORWARD(args)...);
}

template<class... ARGS>
LIBNG_INLINE TempString Fmt(ARGS&&... args) {
  TempString o;
  FmtTo(o, LIBNG_FORWARD(args)...);
  return o;
}

} // namespace libng