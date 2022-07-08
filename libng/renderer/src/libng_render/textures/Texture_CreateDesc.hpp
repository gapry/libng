#pragma once

#include <libng_core/math/Color/ColorType.hpp>

namespace libng {

struct Texture_CreateDesc {
  Texture_CreateDesc();
  ~Texture_CreateDesc();

  String name;
  ColorType colorType;
};

} // namespace libng