#pragma once

#include "platform/os.hpp"
#include "process/process.hpp"

namespace libng {

class daemon : public process {
public:
  daemon();

  ~daemon() = default;

  virtual auto execute(void) -> void override;

  virtual auto job(void) -> void = 0;

private:
  pid_t m_pid = -1;
};

} // namespace libng
