#include "net/io_mux.hpp"

namespace libng {

#if defined(LIBNG_OS_WINDOWS)

LIBNG_INLINE auto poll(libng::span<pollfd_t> fd_set, //
                       int timeout_ms) -> int {      //
  int ret = ::WSAPoll(fd_set.data(),                 //
                      fd_set.size(),                 //
                      timeout_ms);
  return ret;
}
#endif

#if defined(LIBNG_OS_LINUX) || defined(LIBNG_OS_FREEBSD)

LIBNG_INLINE auto poll(libng::span<pollfd_t> fd_set, //
                       int timeout_ms) -> int {      //
  int ret = ::poll(fd_set.data(),                    //
                   fd_set.size(),                    //
                   timeout_ms);                      //
  return ret;
}

#endif

} // namespace libng