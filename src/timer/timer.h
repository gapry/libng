#pragma once

#include "noncopyable.hpp"

namespace gnet {

class timer : public noncopyable<timer> {
public:
  timer() = default;

  ~timer() = default;

  sleep(int);
};

} // namespace gnet
