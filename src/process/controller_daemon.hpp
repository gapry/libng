#pragma once

#include "process/daemon.hpp"

namespace gnet {

class controller_daemon : public daemon {
public:
  controller_daemon() = default;

  ~controller_daemon() = default;

  virtual auto job(void) -> void override;

private:
  pid_t m_pid = -1;
};

} // namespace gnet
