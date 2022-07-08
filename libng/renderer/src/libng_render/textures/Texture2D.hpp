#pragma once

#include <libng_render/RendererCommon.hpp>
#include <libng_render/textures/Texture.hpp>
#include <libng_render/textures/Texture2D_CreateDesc.hpp>

namespace libng {

class Texture2D : public Texture {
public:
  using CreateDesc = Texture2D_CreateDesc;

  Texture2D() = default;
  Texture2D(CreateDesc& desc);
  ~Texture2D();
};

} // namespace libng