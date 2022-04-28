#pragma once

#include "config.hpp"
#include "libng/string.hpp"
#include "noncopyable.hpp"

// clang-format off
#define LIBNG_LOG_INFO(...)    do { libng::g_logger.do_write(libng::logger::level::info,    __VA_ARGS__); } while (false)
#define LIBNG_LOG_WARNING(...) do { libng::g_logger.do_write(libng::logger::level::warning, __VA_ARGS__); } while (false)
#define LIBNG_LOG_ERROR(...)   do { libng::g_logger.do_write(libng::logger::level::error,   __VA_ARGS__); } while (false)
// clang-format on

namespace libng {

class logger : public libng::noncopyable<logger> {
public:
  enum class level
  {
    info,
    warning,
    error,
    unknown,
  };

  logger() = default;

  ~logger() = default;

  auto on_write(libng::logger::level level_type, //
                libng::string_view msg) -> void; //

  template<class... Args>
  auto do_write(libng::logger::level level_type, //
                Args&&... args) -> void {        //
    log_string log_msg;
    fmt_to(log_msg, LIBNG_FORWARD(args)...);
    on_write(level_type, log_msg);
  }
};

extern logger g_logger;

} // namespace libng
