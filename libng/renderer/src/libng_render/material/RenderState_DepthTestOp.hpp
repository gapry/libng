#pragma once

#include <libng_render/RendererCommon.hpp>

namespace libng {

#define RenderState_DepthTestOp_ENUM_LIST(E) \
  E(Less, )                                  \
  E(Equal, )                                 \
  E(LessEqual, )                             \
  E(Greater, )                               \
  E(GreaterEqual, )                          \
  E(NotEqual, )                              \
  E(Always, )                                \
  E(Never, )                                 \
  E(_END, )                                  \
//-----
LIBNG_ENUM_CLASS(RenderState_DepthTestOp, u8)

} // namespace libng