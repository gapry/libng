#pragma once

#include <libng_render/RendererCommon.hpp>

namespace libng {

struct Texture_CreateDesc {
  Texture_CreateDesc();
  ~Texture_CreateDesc();

  String name;
  ColorType colorType;
};

} // namespace libng