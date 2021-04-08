#pragma once

#include "pch.hpp"
#include "platform/os.hpp"

namespace gnet {

class timer {
public:
  timer() = default;

  ~timer() = default;

  auto sleep(int) -> void;
};

} // namespace gnet
