#pragma once

#include "process/daemon/daemon.hpp"

namespace libng {

class login_daemon : public daemon {
public:
  login_daemon() = default;

  ~login_daemon() = default;

  virtual auto job(void) -> void override;

private:
  pid_t m_pid = -1;
};

} // namespace libng
