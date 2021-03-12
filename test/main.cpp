#include <fmt/core.h>

#include "gstring.h"
#include "noncopyable.h"
#include "thread/thread.h"
#include "vector.h"

auto test_noncopyable(void) -> void {
  gnet::noncopyable obj;
}

auto test_vector(void) -> void {
  gnet::vector<int> vec;
  vec.m_vec.push_back(10);
  fmt::print("[log] {}\n", vec.m_vec[0]);
}

auto test_string(void) -> void {
  gnet::string msg;
  msg.m_string = "I go to school by bus.";
  fmt::print("[log] {}\n", msg.m_string);
}

auto test_gnet_thread(void) -> void {
  auto job = [](void) {
    fmt::print("[log] {}\n", __PRETTY_FUNCTION__); //
  };

  std::thread t(job); // gnet::thread t(job);
  t.join();
}

auto main(void) -> int {
  test_noncopyable();
  test_vector();
  test_string();
  test_gnet_thread();
  return 0;
}
