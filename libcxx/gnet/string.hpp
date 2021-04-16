#pragma once

#include <fmt/core.h>
#include <fmt/format.h>

#include <iterator>

#include "config.hpp"
#include "dbg.hpp"
#include "platform/compiler.hpp"
#include "platform/macros.hpp"

namespace gnet::libcxx {

class string {
public:
  string() {
    fmt::print("{}\n", __GNET_PRETTY_FUNCTION__);
  }

  ~string() {
    fmt::print("{}\n", __GNET_PRETTY_FUNCTION__);
  }
};

} // namespace gnet::libcxx

namespace gnet {

template<class... ARGS>
GNET_INLINE auto fmt_to(log_string& out_str,      //
                        ARGS&&... args) -> void { //
  fmt::format_to(std::back_inserter(out_str), GNET_FORWARD(args)...);
}

} // namespace gnet
