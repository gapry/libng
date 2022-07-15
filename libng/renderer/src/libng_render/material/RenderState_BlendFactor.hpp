#pragma once

#include <libng_render/RendererCommon.hpp>

namespace libng {

#define RenderState_BlendFactor_ENUM_LIST(E) \
  E(Zero, )                                  \
  E(One, )                                   \
  E(SrcColor, )                              \
  E(DstColor, )                              \
  E(SrcAlpha, )                              \
  E(DstAlpha, )                              \
  E(ConstColor, )                            \
  /* E(ConstAlpha,) */                       \
  E(OneMinusSrcColor, )                      \
  E(OneMinusDstColor, )                      \
  E(OneMinusSrcAlpha, )                      \
  E(OneMinusDstAlpha, )                      \
  E(OneMinusConstColor, )                    \
  /* E(OneMinusConstAlpha,) */               \
  E(SrcAlphaSaturate, )                      \
  E(_END, )                                  \
//----
LIBNG_ENUM_CLASS(RenderState_BlendFactor, u8)

} // namespace libng