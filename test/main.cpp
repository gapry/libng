#include <test/eastl/vector.hpp>
#include <test/mm/SPtr.hpp>
#include <test/libcxx/vector.hpp>

int main(int, char**) {
  test_eastl();
  test_sptr();
  test_libcxx();
  return 0;
}
