#pragma once

#include "process/daemon/daemon.hpp"

namespace gnet {

class gateway_client_daemon : public daemon {
public:
  gateway_client_daemon() = default;

  ~gateway_client_daemon() = default;

  virtual auto job(void) -> void override;

private:
  pid_t m_pid = -1;
};

} // namespace gnet
