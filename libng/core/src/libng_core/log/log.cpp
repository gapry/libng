#include <fmt/core.h>
#include <libng_core/log/log.hpp>

namespace libng {

Log g_log;

void Log::onWrite(Level lv, StrView str) {
  fmt::print("[{}] {}\n", enumStr(lv), str);
}

} // namespace libng
