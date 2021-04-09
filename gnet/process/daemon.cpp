#include "process/daemon.hpp"

namespace gnet {

#ifdef GNET_OS_WINDOWS
daemon::daemon() {
}
#endif

#if defined(GNET_OS_LINUX) || defined(GNET_OS_FREEBSD)
daemon::daemon() {
  umask(0);
  if (m_pid = spawn_process(); //
      m_pid != 0) {            //
    this->wait_child();
  }
  setsid();
  this->redirect();
}
#endif

auto daemon::execute(void) -> void {
  this->job();
}

} // namespace gnet
