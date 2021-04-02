#ifndef __GNET_ERROR_HANDER_H__
#define __GNET_ERROR_HANDER_H__

#include <exception>
#include <fmt/core.h>

namespace gnet {

class error_handler : public std::exception {
public:
  error_handler(const char* const msg = "") {
    fmt::print("[error] {}\n", msg);
  }
};

} // namespace gnet

#endif
