#pragma once

#include "process/daemon.hpp"

namespace gnet {

class gateway_daemon : public daemon {
public:
  gateway_daemon() = default;

  ~gateway_daemon() = default;

  virtual auto job(void) -> void override;

private:
  pid_t m_pid = -1;
};

} // namespace gnet
