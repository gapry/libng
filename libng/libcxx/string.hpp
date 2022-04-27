#pragma once

#include <fmt/core.h>

namespace libng::libcxx {

class string {
public:
  string() {
    fmt::print("{}\n", __LIBNG_PRETTY_FUNCTION__);
  }

  ~string() {
    fmt::print("{}\n", __LIBNG_PRETTY_FUNCTION__);
  }
};

} // namespace libng::libcxx
