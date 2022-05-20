#pragma once

// std
#include <ostream>

// libng
#include <libcxx/fmt.hpp>
#include <libcxx/string.hpp>
#include <types/function.hpp>

LIBNG_INLINE
std::ostream& operator<<(std::ostream& s, const libng::StrView& v) {
  s.write(v.data(), v.size());
  return s;
}

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
