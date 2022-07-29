#pragma once

#include <libng_core/types/enum.hpp>

namespace libng {

enum class UIEventModifier
{
  None,
  Shift = 1 << 0,
  Ctrl  = 1 << 1,
  Atl   = 1 << 2,
  Cmd   = 1 << 3,
  Fn    = 1 << 4,
};
LIBNG_ENUM_ALL_OPERATOR(UIEventModifier)

} // namespace libng