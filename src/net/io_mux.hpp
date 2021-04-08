#pragma once

#include "config.hpp"
#include "pch.hpp"

#include "platform/compiler.hpp"
#include "platform/macro.hpp"
#include "platform/os.hpp"
#include "platform/types.hpp"

namespace gapry::io_mux {

enum class poll_flags : i16 {
  none    = 0,
  in      = POLLIN,
  out     = POLLOUT,
  inOut   = POLLIN | POLLOUT,
  error   = POLLERR,
  pRI     = POLLPRI,
  hup     = POLLHUP,
  invalid = POLLNVAL,
};

GNET_ENUM_BITWISE_OPERATOR(poll_flags);

#if GNET_OS_WINDOWS
using pollfd_t = ::WSAPOLLFD;
#else
using pollfd_t = ::pollfd;
#endif

GNET_INLINE auto poll(gapry::span<pollfd_t> fd_set, //
                      int timeout_ms) -> int {      //
#if GNET_OS_WINDOWS
  int ret = ::WSAPoll(fd_set.data(), //
                      fd_set.size(), //
                      timeout_ms);   //
#else
  int ret = ::poll(fd_set.data(), //
                   fd_set.size(), //
                   timeout_ms);   //
#endif
  return ret;
}

} // namespace gapry::io_mux
