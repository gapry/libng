#pragma once

#include "error_handler.hpp"
#include "noncopyable.hpp"
#include "pch.hpp"
#include "platform/os.hpp"

namespace libng {

class process : public noncopyable<process> {
public:
  process() = default;

  ~process() = default;

protected:
#ifdef LIBNG_OS_WINDOWS
  using pid_t = int;
#endif

  auto create_process(void) -> pid_t;

  auto wait_child(void) -> pid_t;

  auto redirect(void) -> void;

  virtual auto execute(void) -> void = 0;

private:
  pid_t m_pid        = -1;
  int m_child_status = -1;
};

} // namespace libng
