#pragma once

#include <libng_render/textures/Texture2D.hpp>
#include <libng_render/textures/Texture2D_CreateDesc.hpp>

namespace libng {

class Texture2D_DX11 : public Texture2D {
  using Base = Texture2D;

public:
  Texture2D_DX11(CreateDesc& desc);
  ~Texture2D_DX11();
};

} // namespace libng
