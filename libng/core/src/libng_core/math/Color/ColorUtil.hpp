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

constexpr int ColorUtil::pixelSizeInBytes(ColorUtil::Type t) {
  switch (t) {
    case Type::RGBAb: return sizeof(ColorRGBAb);
  }
  LIBNG_ASSERT(false);
  return 0;
}

// fix: warning C4506: no definition for inline function
constexpr bool ColorUtil::hasAlpha(ColorUtil::Type t) {
  auto model = colorModel(t);
  switch (model) {
    case Model::RGBA: return true;
  }
  return false;
}

// fix: warning C4506: no definition for inline function
constexpr int ColorUtil::bytesPerPixelBlock(ColorUtil::Type type) {
  // clang-format off
  switch (type) {
    #define E(T, ...) case Type::T: return Color##T::kBytesPerPixelBlock;
    //----
    E(BC1)
    E(BC2)
    E(BC3)
    E(BC4)
    E(BC5)
    E(BC6h)
    E(BC7)
    #undef E
  }
  // clang-format on
  return 0;
}

} // namespace libng::math