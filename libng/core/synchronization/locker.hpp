#pragma once

#include "noncopyable.hpp"

#include <mutex>

namespace libng {

class locker : public libng::noncopyable<locker> {
  using mutex_t = std::mutex;

  constexpr locker() noexcept;

  ~locker();

  auto lock() -> void;

  auto try_lock() -> bool;

  auto unlock() -> void;

private:
  mutex_t m_mutex;
};

} // namespace libng
