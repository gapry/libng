#pragma once

#include "process/daemon/daemon.hpp"

namespace gnet {

class zone_manager_daemon : public daemon {
public:
  zone_manager_daemon() = default;

  ~zone_manager_daemon() = default;

  virtual auto job(void) -> void override;

private:
  pid_t m_pid = -1;
};

} // namespace gnet
