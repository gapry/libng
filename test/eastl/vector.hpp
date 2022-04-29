#pragma once

#include <third_party/eastl/eastl.hpp>
#include <fmt/core.h>

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

void test_eastl_vector_push(void) {
  libng::Vector<int> vec;
  init_vector(vec, 8 << 1);
  show_vector(vec);
}