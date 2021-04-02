#pragma once

namespace gnet {

class io {
public:
  io();

  ~io();

  auto read(void) -> void;

  auto write(void) -> void;
};

} // namespace gnet
