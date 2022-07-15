#pragma once

#include <libng_core/exception/error.hpp>
#include <libng_core/math/Color/Color.hpp>

// clang-format off

namespace libng::math {

struct ColorUtil {
  using Type     = libng::math::ColorType;
  using ElemType = libng::math::ColorElementType;
  using Model    = libng::math::ColorModel;
  
  ColorUtil() = delete;

               static constexpr int      pixelSizeInBytes  (Type t);
               static constexpr int      bytesPerPixelBlock(Type t);
               static constexpr bool     hasAlpha          (Type t);
  
  LIBNG_INLINE static constexpr ElemType elementType       (Type t) { return static_cast<ElemType>(enumToInt(t) & 0xff);     }
  LIBNG_INLINE static constexpr Model    colorModel        (Type t) { return static_cast<Model>((enumToInt(t) >> 8) & 0xff); }
};

} // namespace libng::math