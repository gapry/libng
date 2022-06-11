#pragma once

#include <libng_core/types/number.hpp>

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