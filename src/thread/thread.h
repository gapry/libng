#ifndef __GNET_THREAD_H__
#define __GNET_THREAD_H__

#include <noncopyable.h>
#include <thread>

namespace gnet {

class thread : public gnet::noncopyable {
  using thread_t = std::thread;

public:
  template <class func_t, class... arg_t>
  thread(func_t&& f, arg_t&&... args);

  ~thread();

  void join();

  void detach();

  thread& operator=(thread&& other) noexcept;

private:
  thread_t m_thread;
};

} // namespace gnet

#endif
