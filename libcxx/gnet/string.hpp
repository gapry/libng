#pragma once

#include <fmt/core.h>

#include "dbg.hpp"

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
