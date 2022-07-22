#include <libng_render/textures/image/ImageInfo.hpp>

namespace libng {

int ImageInfo::pixelSizeInBytes() const {
  return libng::math::ColorUtil::pixelSizeInBytes(colorType);
}

} // namespace libng