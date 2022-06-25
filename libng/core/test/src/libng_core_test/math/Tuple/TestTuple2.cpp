#include <libng_core/log/variable.hpp>
#include <libng_core/math/Tuple/Tuple2.hpp>

#include <libng_test/unit_test/UnitTestBase.hpp>

namespace libng {

class TestTuple2 : public UnitTestBase {
public:
  void test_ctor() {
    Tuple2f t1(1.0f, 2.0f);
    LIBNG_DUMP_VAR(t1);

    Tuple2d t2(Tuple2d(3.1, 1.4));
    LIBNG_DUMP_VAR(t2);
  }

  void test_set() {
    Tuple2d t1(1.1, 2.2);
    LIBNG_DUMP_VAR(t1);

    Tuple2d t2(Tuple2d(3.1, 1.4));
    LIBNG_DUMP_VAR(t2);

    t2.set(t1);
    LIBNG_DUMP_VAR(t2);
  }
};

} // namespace libng

void test_tuple2() {
  LIBNG_TEST_CASE(libng::TestTuple2, test_ctor());
  LIBNG_TEST_CASE(libng::TestTuple2, test_set());
}
