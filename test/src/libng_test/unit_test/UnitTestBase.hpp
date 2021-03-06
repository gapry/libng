#pragma once

#include <libng_core/exception/error.hpp>
#include <libng_core/log/log.hpp>
#include <libng_core/platform/console_color.hpp>
#include <libng_core/types/enum.hpp>
#include <libng_core/types/noncopyable.hpp>
#include <libng_core/types/number.hpp>

#define LIBNG_TEST_CASE(TestClass, TestFunc)                                               \
  do {                                                                                     \
    LIBNG_LOG("{}[TEST_CASE] {}" #TestClass "." #TestFunc "\n", color_green, color_reset); \
    TestClass testObj;                                                                     \
    testObj.TestFunc;                                                                      \
    LIBNG_LOG("{}\n", "----");                                                             \
  } while (false)

#define LIBNG_VERIFY(TestClass)    LIBNG_TEST_CASE(TestClass, onVerify())

#define LIBNG_TEST_CHECK(a)        LIBNG_TEST_CHECK_IMPL(LIBNG_SRC_LOC, true, bool(a), #a)
#define LIBNG_TEST_CHECK_SLIENT(a) LIBNG_TEST_CHECK_IMPL(LIBNG_SRC_LOC, false, bool(a), #a)

namespace libng {

bool LIBNG_TEST_CHECK_IMPL(const SrcLoc& loc, const bool verbose, const bool success, const char* const msg);

class UnitTestBase : public NonCopyable {
public:
};

} // namespace libng