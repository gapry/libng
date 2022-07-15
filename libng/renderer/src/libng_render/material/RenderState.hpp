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

  struct DepthTest {
    DepthTestOp op = DepthTestOp::LessEqual;
    bool writeMask = true;

    LIBNG_INLINE bool operator==(const DepthTest& rhs) const {
      return op == rhs.op && writeMask == rhs.writeMask;
    }

    LIBNG_INLINE bool isEnable() const {
      return op != DepthTestOp::Always;
    }

    template<class SE>
    void onJson(SE& se) {
      LIBNG_NAMED_IO(se, op);
      LIBNG_NAMED_IO(se, writeMask);
    }
  };

  struct BlendFunc {
    BlendOp op            = BlendOp::Disable;
    BlendFactor srcFactor = BlendFactor::SrcAlpha;
    BlendFactor dstFactor = BlendFactor::OneMinusSrcAlpha;

    void set(BlendOp op_,              //
             BlendFactor srcFactor_,   //
             BlendFactor dstFactor_) { //
      op        = op_;
      srcFactor = srcFactor_;
      dstFactor = dstFactor_;
    }

    template<class SE>
    void onJson(SE& se) {
      LIBNG_NAMED_IO(se, op);
      LIBNG_NAMED_IO(se, srcFactor);
      LIBNG_NAMED_IO(se, dstFactor);
    }
  };

  struct Blend {
    BlendFunc rgb;
    BlendFunc alpha;
    Color4f constColor(1, 1, 1, 1);

    LIBNG_INLINE bool isEnable() const {
      const bool cond1 = BlendOp::Disable != rgb.op;
      const bool cond2 = BlendOp::Disable != alpha.op;
      return cond1 || cond2;
    }

    template<class SE>
    void onJson(SE& se) {
      LIBNG_NAMED_IO(se, rgb);
      LIBNG_NAMED_IO(se, alpha);
      LIBNG_NAMED_IO(se, constColor);
    }
  };

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
