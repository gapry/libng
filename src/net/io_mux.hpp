#pragma once

#include "noncopyable.hpp"
#include "platform/compiler.hpp"

namespace gapry {

class io_mux : public noncopyable<io_mux> {
  class poll {
    enum class PollFlags {
      none    = 0,
      in      = POLLIN,
      out     = POLLOUT,
      inOut   = POLLIN | POLLOUT,
      error   = POLLERR,
      pRI     = POLLPRI,
      hup     = POLLHUP,
      invalid = POLLNVAL,
    };

  public:
    GNET_INLINE auto poll(void) -> int {
      int ret = 0;
      return ret;
    }
  }
};

} // namespace gapry
