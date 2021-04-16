#include <fmt/core.h>

#include "log/log.hpp"

namespace gnet {

logger g_logger;

auto logger::on_write(gnet::logger::level level_type,      //
                      gnet::string_view log_msg) -> void { //
  // fmt::print("{}\n", log_msg);
}

} // namespace gnet
