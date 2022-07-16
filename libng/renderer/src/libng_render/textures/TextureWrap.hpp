#pragma once

#include <libng_render/RendererCommon.hpp>

namespace libng {

#define TextureWrap_ENUM_LIST(E) \
  E(None, )                      \
  E(Repeat, )                    \
  E(Clamp, )                     \
  E(Mirror, )                    \
  E(MirrorOnce, )                \
  E(_END, )                      \
// ----
LIBNG_ENUM_CLASS(TextureWrap, u8)

} // namespace libng