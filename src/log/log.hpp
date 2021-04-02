#ifndef __GNET_LOG_H__
#define __GNET_LOG_H__

#include "io/io.h"
#include "noncopyable.h"
#include "string.h"

namespace gnet {

class log : public gnet::noncopyable, gnet::io {
public:
  enum class level {
    unknown,
    info,
    warning,
    error,
  };

  log() = default;

  ~log() = default;

  void write(gnet::log::level lv, const gnet::string& msg);
};

} // namespace gnet

#endif
