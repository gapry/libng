#pragma once

#include <fmt/core.h>
#include <libcxx/util.hpp>

#include <test/UnitTest/UnitTest.hpp>

namespace libng {

class TestEASTL : public UnitTestBase {
private:
  template<typename T>
  void show_vector(const libng::Vector<T>& vec) {
    for (int i = 0; i < vec.size(); ++i) {
      fmt::print("{} ", vec[i]);
    }
    fmt::print("\n");
  }

  template<typename T>
  void init_vector(libng::Vector<T>& vec, const int elem_size) {
    for (int i = 1; i <= elem_size; ++i) {
      vec.push_back(i);
    }
  }

public:
  void test_eastl_vector_push(void) {
    libng::Vector<int> vec;
    init_vector(vec, 8 << 1);
    show_vector(vec);
  }
};

} // namespace libng