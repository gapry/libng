#pragma once

#include <fmt/format.h>
#include <iterator>

// #include <libng_core/encoding/UtfUtil.hpp> // 'LIBNG_ERROR': identifier not found
#include <libng_core/libcxx/json.hpp>
#include <libng_core/libcxx/string.hpp>
#include <libng_core/platform/compiler.hpp>
#include <libng_core/types/utility.hpp>

#if LIBNG_COMPILER_VC
#if _DEBUG
#pragma comment(lib, "fmtd.lib")
#else
#pragma comment(lib, "fmt.lib")
#endif
#endif

#define LIBNG_FORMATTER(T)                                     \
  } /* namespace libng */                                      \
  template<>                                                   \
  struct fmt::formatter<libng::T> {                            \
    auto parse(fmt::format_parse_context& ctx) {               \
      return ctx.begin();                                      \
    }                                                          \
    auto format(const libng::T& v, fmt::format_context& ctx) { \
      v.onFormat(ctx);                                         \
      return ctx.out();                                        \
    }                                                          \
  };                                                           \
  namespace libng {                                            \
  // ----------

#define LIBNG_FORMATTER_ENUM(T)                                  \
  } /* namespace libng */                                        \
  template<>                                                     \
  struct fmt::formatter<libng::T> {                              \
    auto parse(fmt::format_parse_context& ctx) {                 \
      return ctx.begin();                                        \
    }                                                            \
    auto format(const libng::T& v, fmt::format_context& ctx) {   \
      return fmt::format_to(ctx.out(), "{}", libng::enumStr(v)); \
    }                                                            \
  };                                                             \
  namespace libng {                                              \
  // ----------

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
    libng::TempStringA tmp; // Issue : tmp = libng::UtfUtil::toString(v);
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

// Issue
template<>
struct fmt::formatter<libng::Json> {
  auto parse(fmt::format_parse_context& ctx) {
    return ctx.begin();
  }
  auto format(const libng::Json& v, fmt::format_context& ctx) {
    return fmt::format_to(ctx.out(), "{}", v);
  }
};
