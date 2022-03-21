#include "process/process.hpp"

namespace libng {

#ifdef LIBNG_OS_WINDOWS
auto process::create_process(void) -> pid_t {
}

auto process::wait_child(void) -> pid_t {
}

auto redirect(void) -> void {
}
#endif

#if defined(LIBNG_OS_LINUX) || defined(LIBNG_OS_FREEBSD)
auto process::create_process(void) -> pid_t {
  if ((m_pid = fork()) < 0) {
    throw error_handler("[error] %s.\n", "The system can't create the process");
  }
  return m_pid;
}

auto process::wait_child(void) -> pid_t {
  pid_t wait_child_pid = waitpid(m_pid,           //
                                 &m_child_status, //
                                 0);              //
  if (!WIFEXITED(m_child_status)) {
    throw error_handler("[error] %s.\n", "The child process occurs the error");
  }
  return wait_child_pid;
}

auto redirect(void) -> void {
  int null_fd = ::open("/dev/null", O_RDWR);
  if (null_fd < 0) {
    throw error_handler("[error] %s.\n", "The system can't open /dev/null");
  }
  dup2(null_fd, 0);
  dup2(null_fd, 1);
  dup2(null_fd, 2);
}
#endif

} // namespace libng
