#include <libng_core_test/memory/TestSPtr.hpp>
#include <libng_core_test/memory/TestLinearAllocator.hpp>
#include <libng_core_test/libcxx/TestVector.hpp>
#include <libng_core_test/third_party/eastl/TestEASTL.hpp>
#include <libng_core_test/third_party/imgui/TestImGui.hpp>

int main(int, char**) {
  LIBNG_VERIFY(libng::TestLibcxx);
  LIBNG_VERIFY(libng::TestSPrt);
  LIBNG_VERIFY(libng::TestLinearAllocator);
  LIBNG_TEST_CASE(libng::TestEASTL, onVerify());
  LIBNG_TEST_CASE(libng::TestImGui, onVerify());
  return 0;
}
