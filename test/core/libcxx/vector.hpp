#pragma once

#include <libcxx/vector.hpp>
#include <fmt/core.h>
#include <test/unit_test/base.hpp>

namespace libng {

class TestLibcxx : public UnitTestBase {
private:
  template<typename T>
  void show_libcxx_vector(const libng::libcxx::Vector<T>& v) {
    for (int i = 0; i < v.size(); ++i) {
      fmt::print("{} ", v[i]);
    }
    fmt::print("\n");
  }

public:
  void onVerify() {
    libng::libcxx::Vector<int> v;
    v.resize(11);
    for (int i = 0; i < v.size(); ++i) {
      v[i] = i * 10;
    }
    show_libcxx_vector<int>(v);
  }
};

} // namespace libng