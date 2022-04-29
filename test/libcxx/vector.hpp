#pragma once

#include <libcxx/vector.hpp>
#include <fmt/core.h>

template<typename T>
void show_libcxx_vector(const libng::libcxx::Vector<T>& v) {
  for (int i = 0; i < v.size(); ++i) {
    fmt::print("{} ", v[i]);
  }
  fmt::print("\n");
}

void test_libcxx_vector() {
  libng::libcxx::Vector<int> v;
  v.resize(11);
  for (int i = 0; i < v.size(); ++i) {
    v[i] = i * 10;
  }
  show_libcxx_vector<int>(v);
}

void test_libcxx() {
  test_libcxx_vector();
}