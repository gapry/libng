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

  struct DepthTest {};

  struct Blend {};

  bool wireframe = false;
  Cull cull      = Cull::Back;
  DepthTest depthTest;
  Blend blend;

  template<class SE>
  void onJson(SE& se) {
    LIBNG_NAMED_IO(se, wireframe);
    LIBNG_NAMED_IO(se, cull);
    LIBNG_NAMED_IO(se, depthTest);
    LIBNG_NAMED_IO(se, blend);
  }
};

} // namespace libng
