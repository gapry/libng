#pragma once

#include <types/utility.hpp>
#include <types/noncopyable.hpp>

#include <libcxx/util/fmt.hpp>
#include <libcxx/util/util.hpp>
#include <libcxx/string.hpp>

// clang-format off
#define LIBNG_LOG(...)       do{ libng::g_log.write(libng::Log::Level::Info,    __VA_ARGS__); } while(false)
#define LIBNG_LOG_WARN(...)  do{ libng::g_log.write(libng::Log::Level::Warning, __VA_ARGS__); } while(false)
#define LIBNG_LOG_ERROR(...) do{ libng::g_log.write(libng::Log::Level::Error,   __VA_ARGS__); } while(false)
// clang-format on

namespace libng {

class Log : public NonCopyable {
public:
  enum class Level {
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
};

extern Log g_log;

} // namespace libng
