#include "net/io_mux.hpp"

namespace gnet {

#if defined(GNET_OS_WINDOWS)

GNET_INLINE auto poll(gnet::span<pollfd_t> fd_set, //
                      int timeout_ms) -> int {     //
  int ret = ::WSAPoll(fd_set.data(),               //
                      fd_set.size(),               //
                      timeout_ms);
  return ret;
}
#endif

#if defined(GNET_OS_LINUX) || defined(GNET_OS_FREEBSD)

GNET_INLINE auto poll(gnet::span<pollfd_t> fd_set, //
                      int timeout_ms) -> int {     //
  int ret = ::poll(fd_set.data(),                  //
                   fd_set.size(),                  //
                   timeout_ms);                    //
  return ret;
}

#endif

} // namespace gnet