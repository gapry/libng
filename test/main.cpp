#include <test/core/memory/SPtr.hpp>
#include <test/core/memory/LinearAllocator.hpp>
#include <test/core/libcxx/vector.hpp>

#include <test/compiler/ShaderParser.hpp>

#include <test/third_party/eastl/vector.hpp>
#include <test/third_party/imgui/app.hpp>

int main(int, char**) {
  LIBNG_VERIFY(libng::TestLibcxx);
  LIBNG_VERIFY(libng::TestSPrt);
  LIBNG_VERIFY(libng::TestLinearAllocator);

  LIBNG_TEST_CASE(libng::TestEASTL, onVerify());
  LIBNG_TEST_CASE(libng::TestImGui, onVerify());
  LIBNG_TEST_CASE(libng::TestShaderParser, onVerify());
  return 0;
}
