#pragma once

#include <libng_render/RendererCommon.hpp>

namespace libng {

struct ImageInfo {
public:
  Vec2i size{0, 0};
  int strideInBytes = 0;
  int mipmapCount   = 1;
  ColorType colorType;
};

} // namespace libng