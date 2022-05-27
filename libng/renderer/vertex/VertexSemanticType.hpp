#pragma once

#include <types/number.hpp>

namespace libng {

enum class VertexSemanticType : u8
{
  None,
  Pos,
  Color,
  TexCoord,
  Normal,
  Tangent,
  Binormal,
};

} // namespace libng