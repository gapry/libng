#pragma once

#include <libng_render/RendererCommon.hpp>

namespace libng {

#define RenderState_BlendOp_ENUM_LIST(E) \
  E(Disable, )                           \
  E(Add, )                               \
  E(Sub, )                               \
  E(RevSub, )                            \
  E(Min, )                               \
  E(Max, )                               \
  E(_END, )                              \
//----
LIBNG_ENUM_CLASS(RenderState_BlendOp, u8)

} // namespace libng
