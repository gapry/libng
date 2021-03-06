#include <libng_core/libcxx/limits.hpp>
#include <libng_core/math/Vector/Vec2.hpp>

#include <libng_test/unit_test/UnitTestBase.hpp>

namespace libng {

class TestVec2 : public UnitTestBase {
public:
  using Vec2d = math::Vec2d;

  void test_ctor() {
    Vec2d vec(1.2, 2.3);
    LIBNG_DUMP_VAR(vec);
  }

  void test_operator() {
    auto max = libng::numeric_limits<f64>::max();
    auto min = libng::numeric_limits<f64>::min();

    Vec2d va(max, max);
    Vec2d vb(min, min);

    LIBNG_DUMP_VAR(va);
    LIBNG_DUMP_VAR(vb);

    {
      Vec2d v1 = va + vb; // Issue
      Vec2d v2 = va - vb; // Issue
      Vec2d v3 = va * vb;
      Vec2d v4 = va / vb;

      LIBNG_DUMP_VAR(v1);
      LIBNG_DUMP_VAR(v2);
      LIBNG_DUMP_VAR(v3);
      LIBNG_DUMP_VAR(v4);
    }

    {
      Vec2d v1 = va + max; // Issue
      Vec2d v2 = va - max; // Issue
      Vec2d v3 = va * max;
      Vec2d v4 = va / max;

      LIBNG_DUMP_VAR(v1);
      LIBNG_DUMP_VAR(v2);
      LIBNG_DUMP_VAR(v3);
      LIBNG_DUMP_VAR(v4);
    }

    {
      Vec2d v1;
      Vec2d v2;
      Vec2d v3;
      Vec2d v4;

      v1 += va;
      v2 -= va;
      v3 *= va;
      v4 /= va;

      LIBNG_DUMP_VAR(v1);
      LIBNG_DUMP_VAR(v2);
      LIBNG_DUMP_VAR(v3);
      LIBNG_DUMP_VAR(v4);
    }

    {
      Vec2d v1;
      Vec2d v2;
      Vec2d v3;
      Vec2d v4;

      v1 += min;
      v2 -= min;
      v3 *= min;
      v4 /= min;

      LIBNG_DUMP_VAR(v1);
      LIBNG_DUMP_VAR(v2);
      LIBNG_DUMP_VAR(v3);
      LIBNG_DUMP_VAR(v4);
    }

    {
      Vec2d v(max, min);
      LIBNG_DUMP_VAR(v[0]);
      LIBNG_DUMP_VAR(v[1]);
    }
  }
};

} // namespace libng

void test_vec2() {
  LIBNG_TEST_CASE(libng::TestVec2, test_ctor());
  LIBNG_TEST_CASE(libng::TestVec2, test_operator());
}
