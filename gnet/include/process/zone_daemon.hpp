#pragma once

#include "process/daemon.hpp"

namespace gnet {

class zone_daemon : public daemon {
public:
  zone_daemon() = default;

  ~zone_daemon() = default;

  virtual auto job(void) -> void override;

private:
  pid_t m_pid = -1;
};

} // namespace gnet
