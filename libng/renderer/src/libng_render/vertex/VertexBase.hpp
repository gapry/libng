#pragma once

#include <libng_render/type/RenderDataType.hpp>
#include <libng_render/vertex/VertexType.hpp>
#include <libng_render/vertex/VertexSemantic.hpp>

namespace libng {

struct VertexBase {
  using Semantic = VertexSemantic;

  using PosType    = void;
  using ColorType  = void;
  using UvType     = void;
  using NormalType = void;

  static const RenderDataType kPosType    = RenderDataType::None;
  static const RenderDataType kColorType  = RenderDataType::None;
  static const RenderDataType kUvType     = RenderDataType::None;
  static const RenderDataType kNormalType = RenderDataType::None;

  static const u8 kColorCount    = 0;
  static const u8 kUvCount       = 0;
  static const u8 kNormalCount   = 0;
  static const u8 kTangentCount  = 0;
  static const u8 kBinormalCount = 0;

  static const VertexType kType = VertexType::None;
};

}; // namespace libng