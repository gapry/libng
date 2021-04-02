#ifndef __GNET_CONCURRENCY_H__
#define __GNET_CONCURRENCY_H__

#include "noncopyable.h"

#include <mutex>

namespace gnet {

class locker : public gnet::noncopyable {
  using mutex_t = std::mutex;

  constexpr locker() noexcept;

  ~locker();

  void lock();

  bool try_lock();

  void unlock();

private:
  mutex_t m_mutex;
};

} // namespace gnet

#endif
