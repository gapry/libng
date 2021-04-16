#include "thread/thread.hpp"

template<class func_t, class... arg_t>
gnet::thread::thread(func_t&& f, arg_t&&... args) {
  // m_thread(job);
}

gnet::thread::~thread() {
}

void gnet::thread::join() {
  m_thread.join();
}

void gnet::thread::detach() {
  m_thread.detach();
}

gnet::thread& gnet::thread::operator=(gnet::thread&& other) noexcept {
  return other;
}
