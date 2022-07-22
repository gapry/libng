#pragma once

#include <libng_render/RendererCommon.hpp>

namespace libng {

class Texture_CreateDesc {
  using ColorType = math::ColorType;

public:
  Texture_CreateDesc();
  ~Texture_CreateDesc();

  ColorType colorType = ColorType::RGBAb;
  int mipmapCount     = 1;
  String name;
};

} // namespace libng