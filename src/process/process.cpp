#include "process/process.hpp"

namespace gnet {

auto process::spawn_process(void) -> pid_t {
#ifdef GNET_OS_WINDOWS
#else
  if ((m_pid = fork()) < 0) {
    throw error_handler("[error] %s.\n", "The system can't create the process");
  }
#endif
  return m_pid;
}

auto process::wait_child(void) -> pid_t {
#ifdef GNET_OS_WINDOWS
#else
  pid_t wait_child_pid = waitpid(m_pid,           //
                                 &m_child_status, //
                                 0);              //
  if (!WIFEXITED(m_child_status)) {
    throw error_handler("[error] %s.\n", "The child process occurs the error");
  }
  return wait_child_pid;
#endif
}

auto redirect(void) -> void {
#ifdef GNET_OS_WINDOWS
#else
  int null_fd = ::open("/dev/null", O_RDWR);
  if (null_fd < 0) {
    throw error_handler("[error] %s.\n", "The system can't open /dev/null");
  }
  dup2(null_fd, 0);
  dup2(null_fd, 1);
  dup2(null_fd, 2);
#endif
}

} // namespace gnet
