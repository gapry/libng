#include <libng_core_test/memory/SPtr.hpp>
#include <libng_core_test/memory/LinearAllocator.hpp>
#include <libng_core_test/libcxx/vector.hpp>
#include <libng_core_test/third_party/eastl/vector.hpp>
#include <libng_core_test/third_party/imgui/app.hpp>

int main(int, char**) {
  LIBNG_VERIFY(libng::TestLibcxx);
  LIBNG_VERIFY(libng::TestSPrt);
  LIBNG_VERIFY(libng::TestLinearAllocator);
  LIBNG_TEST_CASE(libng::TestEASTL, onVerify());
  LIBNG_TEST_CASE(libng::TestImGui, onVerify());
  return 0;
}
