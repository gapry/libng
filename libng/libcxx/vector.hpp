#pragma once

#include <fmt/core.h>

#include "dbg.hpp"

namespace libng::libcxx {

template<typename T>
class vector {
public:
  vector() {
    fmt::print("{}\n", __LIBNG_PRETTY_FUNCTION__);
  }

  ~vector() {
    fmt::print("{}\n", __LIBNG_PRETTY_FUNCTION__);
  }
};

} // namespace libng::libcxx
