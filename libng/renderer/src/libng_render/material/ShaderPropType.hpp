#pragma once

namespace libng {

enum class ShaderPropType
{
  None,
  Int,
  Float,
  Vec2f,
  Vec3f,
  Vec4f,
  Color4f,
};

#define ShaderPropType_ENUM_LIST(E) \
  E(Int)                            \
  E(Float)                          \
  E(Vec2f)                          \
  E(Vec3f)                          \
  E(Vec4f)                          \
  E(Color4f)                        \
  // ----

LIBNG_ENUM_STR_UTIL(ShaderPropType)

} // namespace libng