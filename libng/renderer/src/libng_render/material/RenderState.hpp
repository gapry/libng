#pragma once

#include <libng_render/RendererCommon.hpp>
#include <libng_render/material/RenderState_BlendFactor.hpp>
#include <libng_render/material/RenderState_BlendOp.hpp>
#include <libng_render/material/RenderState_Cull.hpp>
#include <libng_render/material/RenderState_DepthTestOp.hpp>

namespace libng {

struct RenderState {
  using Cull        = RenderState_Cull;
  using DepthTestOp = RenderState_DepthTestOp;
  using BlendOp     = RenderState_BlendOp;
  using BlendFactor = RenderState_BlendFactor;

  bool wireframe = false;

  Cull cull = Cull::Back;

  struct DepthTest {};
  DepthTest depthTest;

  struct Blend {};
  Blend blend;
};

} // namespace libng
