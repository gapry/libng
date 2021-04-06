#include "process/daemon.hpp"

namespace gnet {

daemon::daemon() {
#ifdef _WIN32
#else
  umask(0);
  if (m_pid = spawn_process(); //
      m_pid != 0) {            //
    this->wait_child();
  }
  setsid();
  this->redirect();
#endif
}

auto daemon::execute(void) -> void {
  this->job();
}

} // namespace gnet
