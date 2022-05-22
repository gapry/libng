#pragma once

#include <types/number.hpp>
#include <types/enum.hpp>

#include <renderer/vertex/VertexSemanticType.hpp>

namespace libng {

enum class VertexSemantic : u16;

LIBNG_ENUM_ALL_OPERATOR(VertexSemantic);

struct VertexSemanticUtil {
  using Semantic = VertexSemantic;
  using Type     = VertexSemanticType;
  using Index    = u8;

  static constexpr Semantic make(Type type, Index index) {
    return static_cast<Semantic>((enumToInt(type) << 8) | index);
  };

  static constexpr u16 _make(Type type, Index index) {
    return static_cast<u16>(make(type, index));
  };

  static constexpr Type getType(Semantic v) {
    return static_cast<Type>(enumToInt(v) >> 8);
  }

  static constexpr Index getIndex(Semantic v) {
    return static_cast<u8>(enumToInt(v));
  }
};

enum class VertexSemantic : u16 {
  None = 0,
  //
  Pos = VertexSemanticUtil::_make(VertexSemanticType::Pos, 0),
  //
  Color0 = VertexSemanticUtil::_make(VertexSemanticType::Color, 0),
  Color1 = VertexSemanticUtil::_make(VertexSemanticType::Color, 1),
  Color2 = VertexSemanticUtil::_make(VertexSemanticType::Color, 2),
  Color3 = VertexSemanticUtil::_make(VertexSemanticType::Color, 3),
  //
  TexCoord0 = VertexSemanticUtil::_make(VertexSemanticType::TexCoord, 0),
  TexCoord1 = VertexSemanticUtil::_make(VertexSemanticType::TexCoord, 1),
  TexCoord2 = VertexSemanticUtil::_make(VertexSemanticType::TexCoord, 2),
  TexCoord3 = VertexSemanticUtil::_make(VertexSemanticType::TexCoord, 3),
  TexCoord4 = VertexSemanticUtil::_make(VertexSemanticType::TexCoord, 4),
  TexCoord5 = VertexSemanticUtil::_make(VertexSemanticType::TexCoord, 5),
  TexCoord6 = VertexSemanticUtil::_make(VertexSemanticType::TexCoord, 6),
  TexCoord7 = VertexSemanticUtil::_make(VertexSemanticType::TexCoord, 7),
  //
  Normal   = VertexSemanticUtil::_make(VertexSemanticType::Normal, 0),
  Tangent  = VertexSemanticUtil::_make(VertexSemanticType::Tangent, 0),
  Binormal = VertexSemanticUtil::_make(VertexSemanticType::Binormal, 0),
};

} // namespace libng