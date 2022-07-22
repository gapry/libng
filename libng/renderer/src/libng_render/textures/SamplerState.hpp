#pragma once

#include <libng_render/RendererCommon.hpp>
#include <libng_render/textures/TextureFilter.hpp>
#include <libng_render/textures/TextureWrap.hpp>

namespace libng {

struct SamplerState {
  SamplerState();
  ~SamplerState();

  using Filter = TextureFilter;
  using Wrap   = TextureWrap;

  Filter filter = Filter::Bilinear;
  Wrap wrapU    = Wrap::Repeat;
  Wrap wrapV    = Wrap::Repeat;
  Wrap wrapW    = Wrap::Repeat;

  // LOD := Level of Detail
  float minLOD = 0;
  float maxLOD = math::inf<float>();
};

} // namespace libng