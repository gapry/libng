#pragma once

#include <libng_render/RendererCommon.hpp>

namespace libng {

#define RenderState_Cull_ENUM_LIST(E) \
  E(None, )                           \
  E(Back, )                           \
  E(Front, )                          \
  E(_END, )                           \
//----
LIBNG_ENUM_CLASS(RenderState_Cull, u8)

} // namespace libng