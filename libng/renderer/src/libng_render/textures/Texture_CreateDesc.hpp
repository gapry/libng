#pragma once

#include <libng_render/RendererCommon.hpp>

namespace libng {

struct Texture_CreateDesc {
  Texture_CreateDesc();
  ~Texture_CreateDesc();

  String name;
  math::ColorType colorType;
};

} // namespace libng