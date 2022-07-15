#pragma once

#include <libng_core/types/enum.hpp>
#include <libng_core/types/number.hpp>

namespace libng::math {

#define ColorModel_ENUM_LIST(E) \
  E(None, )                     \
  E(R, )                        \
  E(RG, )                       \
  E(RGB, )                      \
  E(RGBA, )                     \
  E(L, )  /* Luminance */       \
  E(LA, ) /* Luminance Alpha */ \
  E(HSV, )                      \
  E(BlockCompression, )         \
//----
LIBNG_ENUM_CLASS(ColorModel, u8)

} // namespace libng::math