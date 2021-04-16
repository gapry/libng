#pragma once

#include <iostream>
#include <iterator>
#include <string_view>

#include <fmt/core.h>
#include <fmt/format.h>

#include <EASTL/fixed_string.h>
#include <EASTL/fixed_vector.h>
#include <EASTL/span.h>
#include <EASTL/string.h>
#include <EASTL/unique_ptr.h>
#include <EASTL/vector.h>

#include "dbg.hpp"

#include "platform/compiler.hpp"
#include "platform/macros.hpp"
#include "platform/os.hpp"

#if !EASTL_DLL
GNET_INLINE auto operator new[](size_t size,          //
                                char const* p_name,   //
                                int flags,            //
                                unsigned debug_flags, //
                                char const* file,     //
                                int line) -> void* {  //
  return malloc(size);
}

GNET_INLINE auto operator new[](size_t size,             //
                                size_t alignment,        //
                                size_t alignment_offset, //
                                char const* p_name,      //
                                int flags,               //
                                unsigned debug_flags,    //
                                char const* file,        //
                                int line) -> void* {     //
#if GNET_OS_WINDOWS
  return _aligned_malloc(size, alignment);
#else
  return std::aligned_alloc(alignment, size);
#endif
}
#endif

namespace gnet {

template<typename T>
using vector = eastl::vector<T>;

template<class T>
using span = eastl::span<T>;

template<class T>
using uptr = eastl::unique_ptr<T>;

template<class T, size_t N, bool is_enable_overflow = true>
using fixed_vector = eastl::fixed_vector<T, N, is_enable_overflow>;

template<class T>
using basic_string_view = eastl::basic_string_view<T>;

using string_view = basic_string_view<char>;

template<class T, size_t N, bool is_enable_overflow = true>
class fixed_string : public eastl::fixed_string<T, N, is_enable_overflow> {
  using base = eastl::fixed_string<T, N, is_enable_overflow>;

public:
  fixed_string() = default;

  ~fixed_string() = default;

  fixed_string(basic_string_view<T> msg)
    : base(msg.data(), msg.size()) {
  }

  fixed_string(fixed_string&& str)
    : base(std::move(str)) {
  }

  template<class R>
  auto operator=(R&& r) -> void {
    base::operator=(GNET_FORWARD(r));
  }
};

using string = eastl::string;

template<size_t N, bool is_enable_overflow = true>
using payload_string = fixed_string<char, N, is_enable_overflow>;

using log_string = payload_string<(128 << 1) - (32 >> 1)>;

template<class... ARGS>
GNET_INLINE auto fmt_to(log_string& out_str,      //
                        ARGS&&... args) -> void { //
  fmt::format_to(std::back_inserter(out_str), GNET_FORWARD(args)...);
}

} // namespace gnet

template<>
struct fmt::formatter<gnet::string_view> {
  auto parse(fmt::format_parse_context& ctx) {
    return ctx.begin();
  }

  auto format(gnet::string_view const& msg, //
              fmt::format_context& ctx) {   //
    std::string_view str_view(msg.data(), msg.size());
    return fmt::format_to(ctx.out(), "{}", str_view);
  }
};
