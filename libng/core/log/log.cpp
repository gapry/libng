#include <log/log.hpp>
#include <fmt/core.h>

namespace libng {

Log g_log;

void Log::onWrite(Level lv, StrView str) {
  fmt::print("{}\n", str);
}

} // namespace libng
