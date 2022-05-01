#include <test/eastl/vector.hpp>
#include <test/mm/SPtr.hpp>
#include <test/libcxx/vector.hpp>
#include <fmt/core.h>

int main(int, char**) {
  test_eastl();
  test_sptr();
  test_libcxx();
  fmt::print("{}\n", __LIBNG_PRETTY_FUNCTION__);
  return 0;
}
