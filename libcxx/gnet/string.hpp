#ifndef __GNET_STRING_H__
#define __GNET_STRING_H__

#include "pch.h"
#include <fmt/core.h>

namespace gnet::beta {

class string {
public:
  string() {
    fmt::print("{}\n", __GNET_PRETTY_FUNCION__);
  }

  ~string() {
    fmt::print("{}\n", __GNET_PRETTY_FUNCION__);
  }
};

} // namespace gnet::beta

#endif
