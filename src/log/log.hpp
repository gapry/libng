#pragma once

#include "config.hpp"
#include "noncopyable.hpp"

#define GNET_LOG_INFO(...)                                                                                             \
  do {                                                                                                                 \
    gnet::g_logger.do_write(gnet::logger::level::info, __VA_ARGS__);                                                   \
  } while (false)

#define GNET_LOG_WARNING(...)                                                                                          \
  do {                                                                                                                 \
    gnet::g_logger.do_write(gnet::logger::level::warning, __VA_ARGS__);                                                \
  } while (false)

#define GNET_LOG_ERROR(...)                                                                                            \
  do {                                                                                                                 \
    gnet::g_logger.do_write(gnet::logger::level::error, __VA_ARGS__);                                                  \
  } while (false)

namespace gnet {

class logger : public gnet::noncopyable<logger> {
public:
  enum class level {
    info,
    warning,
    error,
    unknown,
  };

  logger() = default;

  ~logger() = default;

  auto on_write(gnet::logger::level level_type,   //
                gnet::string const& msg) -> void; //

  template <class... Args>
  auto do_write(gnet::logger::level level_type, //
                Args&&... args) -> void {       //
  }
};

extern logger g_logger;

} // namespace gnet
