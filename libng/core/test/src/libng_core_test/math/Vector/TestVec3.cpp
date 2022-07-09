#include <libng_test/unit_test/UnitTestBase.hpp>

#include <libng_core/libcxx/limits.hpp>
#include <libng_core/math/Tuple/Tuple3.hpp>
#include <libng_core/math/Vector/Vec3.hpp>

namespace libng {

class TestVec3 : public UnitTestBase {
public:
  void test_ctor() {
    {
      Vec3f v1(1.2f, 2.3f, 3.4f);
      LIBNG_DUMP_VAR(v1);
    }
    {
      Tuple3f t1(4.3f, 3.2f, 2.1f);
      Vec3f v1(t1);
      LIBNG_DUMP_VAR(t1);
      LIBNG_DUMP_VAR(v1);
    }
  }
};

} // namespace libng

void test_vec3() {
  LIBNG_TEST_CASE(libng::TestVec3, test_ctor());
}
