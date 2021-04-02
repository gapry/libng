#pragma once

#include <fmt/core.h>

#include "dbg.hpp"

namespace gnet::libcxx {

template <typename T>
class vector {
public:
  vector() {
    fmt::print("{}\n", __GNET_PRETTY_FUNCTION__);
  }

  ~vector() {
    fmt::print("{}\n", __GNET_PRETTY_FUNCTION__);
  }
};

} // namespace gnet::libcxx
