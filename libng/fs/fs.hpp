#pragma once

namespace libng {

class fs {
public:
  fs() = default;

  ~fs();

  auto open(char const* const file_name) -> void;

  auto read(void) -> void;

  auto write(void) -> void;

  auto close(void) -> void;
};

} // namespace libng
