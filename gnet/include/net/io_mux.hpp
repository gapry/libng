#pragma once

#include "config.hpp"
#include "pch.hpp"

#include "platform/compiler.hpp"
#include "platform/macros.hpp"
#include "platform/os.hpp"
#include "platform/types.hpp"

namespace gnet {

enum class poll_flags : i16 {
  none      = 0,
  in        = POLLIN,
  out       = POLLOUT,
  in_or_out = POLLIN | POLLOUT,
  error     = POLLERR,
  pri       = POLLPRI,
  hup       = POLLHUP,
  invalid   = POLLNVAL,
};

GNET_ENUM_BITWISE_OPERATOR(poll_flags);

#if GNET_OS_WINDOWS
using pollfd_t = ::WSAPOLLFD;
#endif

#if defined(GNET_OS_LINUX) || defined(GNET_OS_FREEBSD)
using pollfd_t = ::pollfd;
#endif

GNET_INLINE auto poll(gnet::span<pollfd_t> fd_set, //
                      int timeout_ms) -> int;      //

} // namespace gnet
