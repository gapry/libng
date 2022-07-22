#pragma once

#include <libng_render/RendererCommon.hpp>

namespace libng {

struct ImageInfo {
  int strideInBytes = 0;
  int mipmapCount   = 1;

  math::Vec2i size{0, 0};
  math::ColorType colorType = math::ColorType::None;

  int pixelSizeInBytes() const;
};

} // namespace libng