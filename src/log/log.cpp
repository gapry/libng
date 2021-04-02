#include <fmt/core.h>

#include "log/log.hpp"

log gnet_logger;

auto gnet::logger::on_write(gnet::logger::level level_type,    //
                            gnet::string const& msg) -> void { //
  fmt::print("{}\n", msg);
}
