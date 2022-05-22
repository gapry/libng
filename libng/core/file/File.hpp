#pragma once

#include <types/number.hpp>

namespace libng {

using FileSize = u64;

enum class FileMode {
  CreateNew,
  OpenExists,
  OpenOrCreate,
};

enum class FileAccess {
  Read,
  ReadWrite,
  WriteOnly,
};

enum class FileShareMode {
  None,
  Read,
  Write,
  ReadWrite,
};

} // namespace libng