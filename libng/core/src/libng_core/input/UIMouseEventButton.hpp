#pragma once

#include <libng_core/types/enum.hpp>

namespace libng {

enum class UIMouseEventButton
{
  None,
  Left    = 1 << 0,
  Middle  = 1 << 1,
  Right   = 1 << 2,
  Button4 = 1 << 3,
  Button5 = 1 << 4,
};
LIBNG_ENUM_ALL_OPERATOR(UIMouseEventButton)

} // namespace libng