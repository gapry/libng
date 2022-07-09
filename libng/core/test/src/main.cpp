#include <libng_core/log/log.hpp>
#include <libng_core/platform/console_color.hpp>

#define LIBNG_RUN_TEST(fn)                                                                  \
  LIBNG_LOG("================ " color_blue "[" #fn "]" color_reset " ================ \n"); \
  void fn();                                                                                \
  fn();                                                                                     \
  // -----

namespace libng {

void run_temp_test() {
  LIBNG_RUN_TEST(test_vec3);
}

void run_math_test() {
  LIBNG_RUN_TEST(test_tuple2);
  LIBNG_RUN_TEST(test_vec2);
  LIBNG_RUN_TEST(test_vec3);
}

void run_file_test() {
  LIBNG_RUN_TEST(test_file);
  LIBNG_RUN_TEST(test_mem_map_file);
  LIBNG_RUN_TEST(test_json_file);
}

void run_libcxx_test() {
  LIBNG_RUN_TEST(test_unique_ptr);
  LIBNG_RUN_TEST(test_string);
}

void run_core_test() {
  run_libcxx_test();
  run_file_test();
  run_math_test();
}

void run_third_party_test() {
  LIBNG_RUN_TEST(test_eastl_fixed_vector);
  LIBNG_RUN_TEST(test_json);
}

void run_all_test() {
  run_core_test();
  run_libcxx_test();
  run_third_party_test();

  // LIBNG_VERIFY(TestLibcxx);
  // LIBNG_VERIFY(TestSPrt);
  // LIBNG_VERIFY(TestLinearAllocator);
}

int test_main(void) {
#if 1
  run_temp_test();
#else
  run_all_test();
#endif
  return 0;
}

} // namespace libng

int main(int, char**) {
  return libng::test_main();
}