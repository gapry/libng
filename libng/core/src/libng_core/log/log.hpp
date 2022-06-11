#pragma once

#include <libng_core/types/utility.hpp>
#include <libng_core/types/noncopyable.hpp>
#include <libng_core/types/function.hpp>
#include <libng_core/exception/error.hpp>
#include <libng_core/libcxx/fmt.hpp>
#include <libng_core/libcxx/string.hpp>

// clang-format off
#define LIBNG_LOG(...)       do{ libng::g_log.write(libng::Log::Level::Info,    __VA_ARGS__); } while(false)
#define LIBNG_LOG_WARN(...)  do{ libng::g_log.write(libng::Log::Level::Warning, __VA_ARGS__); } while(false)
#define LIBNG_LOG_ERROR(...) do{ libng::g_log.write(libng::Log::Level::Error,   __VA_ARGS__); } while(false)
// clang-format on

namespace libng {

class Log : public NonCopyable {
public:
  enum class Level
  {
    Unknown,
    Info,
    Warning,
    Error,
  };

  template<class... Args>
  void write(Level lv, Args&&... args) {
    TempString tmp;
    FmtTo(tmp, LIBNG_FORWARD(args)...);
    onWrite(lv, tmp);
  }

  void onWrite(Level lv, StrView str);

  String enumStr(Log::Level level);
};

LIBNG_INLINE
String Log::enumStr(Log::Level level) {
  using E = Log::Level;
  switch (level) {
    // clang-format off
    case E::Unknown:  return "Unknown";
    case E::Info:     return "Info";
    case E::Warning:  return "Warning";
    case E::Error:    return "Error";
    // clang-format on
    default: {
      LIBNG_ASSERT(false);
      return "";
    }
  }
}

extern Log g_log;

} // namespace libng
