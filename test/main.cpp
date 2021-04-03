#include <fmt/core.h>

#include "gnet/string.hpp"
#include "gnet/vector.hpp"

#include "config.hpp"

#include "thread/thread.hpp"

auto test_gnet_vector(void) -> void {
  gnet::libcxx::vector<int> v1;
  gnet::vector<int> v2;
  v2.push_back(11);
  fmt::print("{}\n", v2[0]);
}

auto test_gnet_string(void) -> void {
  gnet::libcxx::string msg1;
  gnet::string msg2 = "I go to school by bus";
  fmt::print("{}\n", msg2);
}

auto test_gnet_thread(void) -> void {
  auto job = [](void) {
    fmt::print("[log] {}\n", __PRETTY_FUNCTION__); //
  };

  std::thread t(job); // gnet::thread t(job);
  t.join();
}

auto main(void) -> int {
  test_gnet_vector();
  test_gnet_string();
  test_gnet_thread();
  return 0;
}
