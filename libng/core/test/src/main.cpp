#include <libng_core/log/log.hpp>
#include <libng_core_test/memory/TestSPtr.hpp>
#include <libng_core_test/memory/TestLinearAllocator.hpp>
#include <libng_core_test/libcxx/TestVector.hpp>
#include <libng_core_test/third_party/eastl/TestEASTL.hpp>
#include <libng_core_test/third_party/imgui/TestImGui.hpp>

#define LIBNG_RUN_TEST(fn)                     \
  LIBNG_LOG("======== [" #fn "] ======== \n"); \
  void fn();                                   \
  fn();                                        \
  // -----

namespace libng {

void run_temp_test() {
  LIBNG_RUN_TEST(test_unique_ptr);
}

void run_all_test() {
  LIBNG_VERIFY(TestLibcxx);
  LIBNG_VERIFY(TestSPrt);
  LIBNG_VERIFY(TestLinearAllocator);
  LIBNG_TEST_CASE(TestEASTL, onVerify());
  LIBNG_TEST_CASE(TestImGui, onVerify());
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