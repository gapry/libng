#pragma once

#include <exception>
#include <fmt/core.h>

namespace gnet {

class error_handler : public std::exception {
public:
  error_handler(char const* const fmt,        //
                char const* const msg = "") { //
    fmt::print(stderr, fmt, msg);
  }
};

} // namespace gnet
