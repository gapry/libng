#ifndef __GNET_VERCTOR_H__
#define __GNET_VERCTOR_H__

#include <fmt/core.h>

#include "pch.h"

namespace gnet::beta {

template <typename T>
class vector {
public:
  vector() {
    fmt::print("{}\n", __GNET_PRETTY_FUNCION__);
  }

  ~vector() {
    fmt::print("{}\n", __GNET_PRETTY_FUNCION__);
  }
};

} // namespace gnet::beta

#endif
