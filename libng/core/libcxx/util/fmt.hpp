#pragma once

#include <platform/compiler.hpp>
#include <types/utility.hpp>
#include <libcxx/util/util.hpp>

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

template<>
struct fmt::formatter<libng::StrView> {
  auto parse(fmt::format_parse_context& ctx) {
    return ctx.begin();
  }
  auto format(const libng::StrView& v, fmt::format_context& ctx) {
    auto it = *ctx.out();
    for (const auto& c : v) {
      it = c;
      it++;
    }
    return ctx.out();
  }
};

template<>
struct fmt::formatter<libng::String> {
  auto parse(fmt::format_parse_context& ctx) {
    return ctx.begin();
  }
  auto format(const libng::String& v, fmt::format_context& ctx) {
    libng::StrView view(v.data(), v.size());
    return fmt::format_to(ctx.out(), "{}", view);
  }
};

template<size_t N>
struct fmt::formatter<libng::String_<N>> {
  auto parse(fmt::format_parse_context& ctx) {
    return ctx.begin();
  }
  auto format(const libng::String_<N>& v, fmt::format_context& ctx) {
    libng::StrView view(v.data(), v.size());
    return fmt::format_to(ctx.out(), "{}", view);
  }
};

template<>
struct fmt::formatter<libng::StrViewW> {
  auto parse(fmt::format_parse_context& ctx) {
    return ctx.begin();
  }
  auto format(const libng::StrViewW& v, fmt::format_context& ctx) {
    libng::TempStringA tmp; // Issue: = libng::UtfUtil::toString(v);
    return fmt::format_to(ctx.out(), "{}", tmp);
  }
};

template<>
struct fmt::formatter<libng::StringW> {
  auto parse(fmt::format_parse_context& ctx) {
    return ctx.begin();
  }
  auto format(const libng::StringW& v, fmt::format_context& ctx) {
    libng::StrViewW view(v.data(), v.size());
    return fmt::format_to(ctx.out(), "{}", view);
  }
};

template<size_t N>
struct fmt::formatter<libng::StringW_<N>> {
  auto parse(fmt::format_parse_context& ctx) {
    return ctx.begin();
  }
  auto format(const libng::StringW_<N>& v, fmt::format_context& ctx) {
    libng::StrViewW view(v.data(), v.size());
    return fmt::format_to(ctx.out(), "{}", view);
  }
};
