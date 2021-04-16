#pragma once

#include <fmt/core.h>

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
