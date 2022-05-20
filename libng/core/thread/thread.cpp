#include "thread/thread.hpp"

template<class func_t, class... arg_t>
libng::thread::thread(func_t&& f, arg_t&&... args) {
  // m_thread(job);
}

libng::thread::~thread() {
}

void libng::thread::join() {
  m_thread.join();
}

void libng::thread::detach() {
  m_thread.detach();
}

libng::thread& libng::thread::operator=(libng::thread&& other) noexcept {
  return other;
}
