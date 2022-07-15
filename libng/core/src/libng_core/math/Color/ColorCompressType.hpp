#pragma once

#include <libng_core/types/enum.hpp>
#include <libng_core/types/number.hpp>

namespace libng::math {

#define ColorCompressType_ENUM_LIST(E) \
  E(None, )                            \
  E(BC1, )                             \
  E(BC2, )                             \
  E(BC3, )                             \
  E(BC4, )                             \
  E(BC5, )                             \
  E(BC6h, )                            \
  E(BC7, )                             \
//-------
LIBNG_ENUM_CLASS(ColorCompressType, u8);

} // namespace libng::math