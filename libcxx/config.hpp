#pragma once

#include <EASTL/fixed_string.h>
#include <EASTL/fixed_vector.h>
#include <EASTL/span.h>
#include <EASTL/string.h>
#include <EASTL/unique_ptr.h>
#include <EASTL/vector.h>

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

} // namespace gnet
