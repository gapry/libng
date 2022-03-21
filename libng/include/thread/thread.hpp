#pragma once

#include "noncopyable.hpp"

#include <thread>

namespace libng {

class thread : public libng::noncopyable<thread> {
  using thread_t = std::thread;

public:
  template<class func_t, class... arg_t>
  thread(func_t&& f, arg_t&&... args);

  ~thread();

  void join();

  void detach();

  thread& operator=(thread&& other) noexcept;

private:
  thread_t m_thread;
};

} // namespace libng
