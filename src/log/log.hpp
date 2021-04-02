#pragma once

#include "io/io.hpp"
#include "noncopyable.hpp"
#include "string.hpp"

namespace gnet {

class log : public gnet::noncopyable<log>, gnet::io {
public:
  enum class level {
    unknown,
    info,
    warning,
    error,
  };

  log() = default;

  ~log() = default;

  auto write(gnet::log::level lv, const gnet::string& msg) -> void;
};

} // namespace gnet
