#pragma once

#include <libng_core/types/enum.hpp>
#include <libng_core/types/number.hpp>

namespace libng {

enum class VertexSemanticType : u8
{
  None,
  POSITION,
  COLOR,
  TEXCOORD,
  NORMAL,
  TANGENT,
  BINORMAL,
};

#define VertexSemanticType_ENUM_LIST(E) \
  E(None)                               \
  E(POSITION)                           \
  E(COLOR)                              \
  E(TEXCOORD)                           \
  E(NORMAL)                             \
  E(TANGENT)                            \
  E(BINORMAL)                           \
//----
LIBNG_ENUM_STR_UTIL(VertexSemanticType)

} // namespace libng