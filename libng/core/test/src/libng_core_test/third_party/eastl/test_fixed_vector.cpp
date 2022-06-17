#pragma once

#include <fmt/core.h>
#include <libng_core/types/number.hpp>
#include <libng_core/libcxx/fixed_vector.hpp>
#include <libng_test/unit_test/UnitTestBase.hpp>

namespace libng {

class test_eastl_fixed_vector : public UnitTestBase {
  using vec_t = Vector_<f32, 16>;

  vec_t dataset;

  void print() {
    for (auto& data : dataset) {
      fmt::print("{} ", data);
    }
    fmt::print("\n");
  }

  // Issue
  // void reset(const vec_t& dataset) {
  //   dataset.emplace_back(1.2f); // Issue
  // }

  void reset() {
    dataset.emplace_back(1.2f);
    dataset.emplace_back(2.3f);
    dataset.emplace_back(3.4f);
    dataset.emplace_back(4.5f);
  }

public:
  void test_back() {
    dataset = vec_t();
    reset();
    print();
    fmt::print("back = {}\n", dataset.back());
  }

  void test_pop_back() {
    dataset = vec_t();
    reset();
    print();
    fmt::print("{}\n", "-------");

    dataset.pop_back();
    print();
  }
};

} // namespace libng

void test_eastl_fixed_vector() {
  LIBNG_TEST_CASE(libng::test_eastl_fixed_vector, test_back());
  LIBNG_TEST_CASE(libng::test_eastl_fixed_vector, test_pop_back());
}