#include <fmt/core.h>

#include "log/log.hpp"

namespace libng {

logger g_logger;

auto logger::on_write(libng::logger::level level_type,      //
                      libng::string_view log_msg) -> void { //
  fmt::print("{}\n", log_msg);
}

} // namespace libng
