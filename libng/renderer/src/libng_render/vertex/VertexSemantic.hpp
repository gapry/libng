#pragma once

#include <libng_core/types/number.hpp>
#include <libng_core/types/enum.hpp>
#include <libng_render/vertex/VertexSemanticType.hpp>

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

enum class VertexSemantic : u16
{
  None = 0,

  POSITION = VertexSemanticUtil::_make(VertexSemanticType::POSITION, 0),

  COLOR0 = VertexSemanticUtil::_make(VertexSemanticType::COLOR, 0),
  COLOR1 = VertexSemanticUtil::_make(VertexSemanticType::COLOR, 1),
  COLOR2 = VertexSemanticUtil::_make(VertexSemanticType::COLOR, 2),
  COLOR3 = VertexSemanticUtil::_make(VertexSemanticType::COLOR, 3),

  TEXCOORD0 = VertexSemanticUtil::_make(VertexSemanticType::TEXCOORD, 0),
  TEXCOORD1 = VertexSemanticUtil::_make(VertexSemanticType::TEXCOORD, 1),
  TEXCOORD2 = VertexSemanticUtil::_make(VertexSemanticType::TEXCOORD, 2),
  TEXCOORD3 = VertexSemanticUtil::_make(VertexSemanticType::TEXCOORD, 3),
  TEXCOORD4 = VertexSemanticUtil::_make(VertexSemanticType::TEXCOORD, 4),
  TEXCOORD5 = VertexSemanticUtil::_make(VertexSemanticType::TEXCOORD, 5),
  TEXCOORD6 = VertexSemanticUtil::_make(VertexSemanticType::TEXCOORD, 6),
  TEXCOORD7 = VertexSemanticUtil::_make(VertexSemanticType::TEXCOORD, 7),
  TEXCOORD8 = VertexSemanticUtil::_make(VertexSemanticType::TEXCOORD, 8),
  TEXCOORD9 = VertexSemanticUtil::_make(VertexSemanticType::TEXCOORD, 9),

  TEXCOORD10 = VertexSemanticUtil::_make(VertexSemanticType::TEXCOORD, 10),
  TEXCOORD11 = VertexSemanticUtil::_make(VertexSemanticType::TEXCOORD, 11),
  TEXCOORD12 = VertexSemanticUtil::_make(VertexSemanticType::TEXCOORD, 12),
  TEXCOORD13 = VertexSemanticUtil::_make(VertexSemanticType::TEXCOORD, 13),
  TEXCOORD14 = VertexSemanticUtil::_make(VertexSemanticType::TEXCOORD, 14),
  TEXCOORD15 = VertexSemanticUtil::_make(VertexSemanticType::TEXCOORD, 15),
  TEXCOORD16 = VertexSemanticUtil::_make(VertexSemanticType::TEXCOORD, 16),
  TEXCOORD17 = VertexSemanticUtil::_make(VertexSemanticType::TEXCOORD, 17),
  TEXCOORD18 = VertexSemanticUtil::_make(VertexSemanticType::TEXCOORD, 18),
  TEXCOORD19 = VertexSemanticUtil::_make(VertexSemanticType::TEXCOORD, 19),

  TEXCOORD20 = VertexSemanticUtil::_make(VertexSemanticType::TEXCOORD, 20),
  TEXCOORD21 = VertexSemanticUtil::_make(VertexSemanticType::TEXCOORD, 21),
  TEXCOORD22 = VertexSemanticUtil::_make(VertexSemanticType::TEXCOORD, 22),
  TEXCOORD23 = VertexSemanticUtil::_make(VertexSemanticType::TEXCOORD, 23),
  TEXCOORD24 = VertexSemanticUtil::_make(VertexSemanticType::TEXCOORD, 24),
  TEXCOORD25 = VertexSemanticUtil::_make(VertexSemanticType::TEXCOORD, 25),
  TEXCOORD26 = VertexSemanticUtil::_make(VertexSemanticType::TEXCOORD, 26),
  TEXCOORD27 = VertexSemanticUtil::_make(VertexSemanticType::TEXCOORD, 27),
  TEXCOORD28 = VertexSemanticUtil::_make(VertexSemanticType::TEXCOORD, 28),
  TEXCOORD29 = VertexSemanticUtil::_make(VertexSemanticType::TEXCOORD, 29),

  TEXCOORD30 = VertexSemanticUtil::_make(VertexSemanticType::TEXCOORD, 30),
  TEXCOORD31 = VertexSemanticUtil::_make(VertexSemanticType::TEXCOORD, 31),
  TEXCOORD32 = VertexSemanticUtil::_make(VertexSemanticType::TEXCOORD, 32),
  TEXCOORD33 = VertexSemanticUtil::_make(VertexSemanticType::TEXCOORD, 33),
  TEXCOORD34 = VertexSemanticUtil::_make(VertexSemanticType::TEXCOORD, 34),
  TEXCOORD35 = VertexSemanticUtil::_make(VertexSemanticType::TEXCOORD, 35),
  TEXCOORD36 = VertexSemanticUtil::_make(VertexSemanticType::TEXCOORD, 36),
  TEXCOORD37 = VertexSemanticUtil::_make(VertexSemanticType::TEXCOORD, 37),
  TEXCOORD38 = VertexSemanticUtil::_make(VertexSemanticType::TEXCOORD, 38),
  TEXCOORD39 = VertexSemanticUtil::_make(VertexSemanticType::TEXCOORD, 39),

  NORMAL   = VertexSemanticUtil::_make(VertexSemanticType::NORMAL, 0),
  TANGENT  = VertexSemanticUtil::_make(VertexSemanticType::TANGENT, 0),
  BINORMAL = VertexSemanticUtil::_make(VertexSemanticType::BINORMAL, 0),
};

#define VertexSemantic_ENUM_LIST(E) \
  E(None)                           \
  E(POSITION)                       \
                                    \
  E(COLOR0)                         \
  E(COLOR1)                         \
  E(COLOR2)                         \
  E(COLOR3)                         \
                                    \
  E(TEXCOORD0)                      \
  E(TEXCOORD1)                      \
  E(TEXCOORD2)                      \
  E(TEXCOORD3)                      \
  E(TEXCOORD4)                      \
  E(TEXCOORD5)                      \
  E(TEXCOORD6)                      \
  E(TEXCOORD7)                      \
  E(TEXCOORD8)                      \
  E(TEXCOORD9)                      \
                                    \
  E(TEXCOORD10)                     \
  E(TEXCOORD11)                     \
  E(TEXCOORD12)                     \
  E(TEXCOORD13)                     \
  E(TEXCOORD14)                     \
  E(TEXCOORD15)                     \
  E(TEXCOORD16)                     \
  E(TEXCOORD17)                     \
  E(TEXCOORD18)                     \
  E(TEXCOORD19)                     \
                                    \
  E(TEXCOORD20)                     \
  E(TEXCOORD21)                     \
  E(TEXCOORD22)                     \
  E(TEXCOORD23)                     \
  E(TEXCOORD24)                     \
  E(TEXCOORD25)                     \
  E(TEXCOORD26)                     \
  E(TEXCOORD27)                     \
  E(TEXCOORD28)                     \
  E(TEXCOORD29)                     \
                                    \
  E(TEXCOORD30)                     \
  E(TEXCOORD31)                     \
  E(TEXCOORD32)                     \
  E(TEXCOORD33)                     \
  E(TEXCOORD34)                     \
  E(TEXCOORD35)                     \
  E(TEXCOORD36)                     \
  E(TEXCOORD37)                     \
  E(TEXCOORD38)                     \
  E(TEXCOORD39)                     \
                                    \
  E(NORMAL)                         \
  E(TANGENT)                        \
  E(BINORMAL)                       \
//----
LIBNG_ENUM_STR_UTIL(VertexSemantic)

} // namespace libng