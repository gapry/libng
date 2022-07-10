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
    {
      // Issue:  warning C4305: 'argument': truncation from 'double' to 'const T' with [T=libng::f32]
      //
      // Vec2f v1(1.2, -2.1);
      // LIBNG_DUMP_VAR(v1);

      // Vec3f v2(v1, 1.2);
      // LIBNG_DUMP_VAR(v2);
    } {
      Vec2f v1(1.2f, -2.1f);
      LIBNG_DUMP_VAR(v1);

      Vec3f v2(v1, 1.2f);
      LIBNG_DUMP_VAR(v2);
    }
  }

  void test_static_method() {
    auto print = [](const Vec3f& vec) -> void {
      LIBNG_DUMP_VAR(vec);
    };

    print(Vec3f::s_inf());

    print(Vec3f::s_zero());
    print(Vec3f::s_one());

    print(Vec3f::s_forward());
    print(Vec3f::s_back());

    print(Vec3f::s_up());
    print(Vec3f::s_down());

    print(Vec3f::s_left());
    print(Vec3f::s_right());
  }
};

} // namespace libng

void test_vec3() {
  LIBNG_TEST_CASE(libng::TestVec3, test_ctor());
  LIBNG_TEST_CASE(libng::TestVec3, test_static_method());
}
