#pragma once

#include <libng_core/log/log.hpp>
#include <libng_core/types/noncopyable.hpp>
#include <libng_core/exception/error.hpp>

#define LIBNG_TEST_CASE(TestClass, TestFunc)                    \
  do {                                                          \
    LIBNG_LOG("\n [TEST_CASE] " #TestClass "." #TestFunc "\n"); \
    TestClass testObj;                                          \
    testObj.TestFunc;                                           \
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