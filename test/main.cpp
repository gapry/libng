#include <test/eastl/vector.hpp>
#include <test/mm/SPtr.hpp>
#include <test/libcxx/vector.hpp>
#include <fmt/core.h>

int main(int, char**) {
  LIBNG_TEST_CASE(libng::TestLibcxx, test_libcxx_vector());
  LIBNG_TEST_CASE(libng::TestSPrt, test_sptr());
  LIBNG_TEST_CASE(libng::TestEASTL, test_eastl_vector_push());
  return 0;
}
