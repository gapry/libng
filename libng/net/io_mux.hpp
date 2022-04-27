#pragma once

#include "config.hpp"
#include "pch.hpp"

#include "platform/compiler.hpp"
#include "platform/macros.hpp"
#include "platform/os.hpp"
#include "platform/types.hpp"

namespace libng {

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

LIBNG_ENUM_BITWISE_OPERATOR(poll_flags);

#if LIBNG_OS_WINDOWS
using pollfd_t = ::WSAPOLLFD;
#endif

#if defined(LIBNG_OS_LINUX) || defined(LIBNG_OS_FREEBSD)
using pollfd_t = ::pollfd;
#endif

LIBNG_INLINE auto poll(libng::span<pollfd_t> fd_set, //
                       int timeout_ms) -> int;       //

} // namespace libng
