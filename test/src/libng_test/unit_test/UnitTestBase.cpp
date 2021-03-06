#include <cassert>
#include <fmt/core.h>
#include <libng_test/unit_test/UnitTestBase.hpp>

namespace libng {

bool LIBNG_TEST_CHECK_IMPL(const SrcLoc& loc, const bool verbose, const bool success, const char* const msg) {
  if (success && !verbose) {
    return success;
  }

  auto str = fmt::format("{} {}\n", (success ? "[ OK ]" : "[ FAIL ]"), msg);
  fmt::print("{}", str);

  if (!success) {
    assert(false);
  }
  return success;
}

} // namespace libng