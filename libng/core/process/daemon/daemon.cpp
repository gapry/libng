#include "process/daemon/daemon.hpp"

namespace libng {

#ifdef LIBNG_OS_WINDOWS
daemon::daemon() {
}
#endif

#if defined(LIBNG_OS_LINUX) || defined(LIBNG_OS_FREEBSD)
daemon::daemon() {
  umask(0);
  if (m_pid = create_process(); //
      m_pid != 0) {             //
    this->wait_child();
  }
  setsid();
  this->redirect();
}
#endif

auto daemon::execute(void) -> void {
  this->job();
}

} // namespace libng
