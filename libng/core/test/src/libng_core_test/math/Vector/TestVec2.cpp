#include <libng_core/libcxx/limits.hpp>
#include <libng_core/log/variable.hpp>
#include <libng_core/math/Vector/Vec2.hpp>

#include <libng_test/unit_test/UnitTestBase.hpp>

namespace libng {

class TestVec2 : public UnitTestBase {
public:
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

    Vec2d v1 = va + vb; // Issue
    Vec2d v2 = va - vb; // Issue
    Vec2d v3 = va * vb;
    Vec2d v4 = va / vb;

    LIBNG_DUMP_VAR(v1);
    LIBNG_DUMP_VAR(v2);
    LIBNG_DUMP_VAR(v3);
    LIBNG_DUMP_VAR(v4);
  }
};

} // namespace libng

void test_vec2() {
  LIBNG_TEST_CASE(libng::TestVec2, test_ctor());
  LIBNG_TEST_CASE(libng::TestVec2, test_operator());
}
