#pragma once

#include <libng_render/RendererCommon.hpp>

namespace libng {

#define ShaderPropType_ENUM_LIST(E) \
  E(None, )                         \
  E(Int, )                          \
  E(Float, )                        \
  E(Vec2f, )                        \
  E(Vec3f, )                        \
  E(Vec4f, )                        \
  E(Color4f, )                      \
  E(Texture2d, )                    \
  // ----

LIBNG_ENUM_CLASS(ShaderPropType, u8)

} // namespace libng