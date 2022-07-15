#include <libng_core/math/Color/ColorUtil.hpp>

namespace libng::math {

constexpr int ColorUtil::pixelSizeInBytes(ColorUtil::Type t) {
  switch (t) {
    case Type::RGBAb: return sizeof(ColorRGBAb);
  }
  LIBNG_ASSERT(false);
  return 0;
}

// clang-format off
constexpr int ColorUtil::bytesPerPixelBlock(ColorUtil::Type type) {
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
  return 0;
}
// clang-format on

constexpr bool ColorUtil::hasAlpha(ColorUtil::Type t) {
  auto model = colorModel(t);
  switch (model) {
    case Model::RGBA: return true;
  }
  return false;
}

} // namespace libng::math