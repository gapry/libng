#pragma once

#include <libng_core/types/enum.hpp>

namespace libng {

enum class UIMouseEventType
{
  None,
  Up,
  Down,
  Move,
  Scroll,
};
LIBNG_ENUM_ALL_OPERATOR(UIMouseEventType)

} // namespace libng