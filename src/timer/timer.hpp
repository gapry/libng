#ifndef __GNET_TIMER_H__
#define __GNET_TIMER_H__

#include "pch.hpp"
#include "platform/os.hpp"

namespace gnet {

class timer {
public:
  timer() = default;

  ~timer() = default;

  sleep(int);
};

} // namespace gnet

#endif
