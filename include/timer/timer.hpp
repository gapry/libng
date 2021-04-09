#pragma once

#include "noncopyable.hpp"
#include "pch.hpp"
#include "platform/os.hpp"

namespace gnet {

class timer : public noncopyable<timer> {
public:
  timer() = default;

  ~timer() = default;

  auto sleep(int) -> void;
};

} // namespace gnet
