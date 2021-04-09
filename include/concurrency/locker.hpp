#pragma once

#include "noncopyable.hpp"

#include <mutex>

namespace gnet {

class locker : public gnet::noncopyable<locker> {
  using mutex_t = std::mutex;

  constexpr locker() noexcept;

  ~locker();

  auto lock() -> void;

  auto try_lock() -> bool;

  auto unlock() -> void;

private:
  mutex_t m_mutex;
};

} // namespace gnet
