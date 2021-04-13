#pragma once

#include "process/daemon/daemon.hpp"

namespace gnet {

class gateway_server_daemon : public daemon {
public:
  gateway_server_daemon() = default;

  ~gateway_server_daemon() = default;

  virtual auto job(void) -> void override;

private:
  pid_t m_pid = -1;
};

} // namespace gnet
