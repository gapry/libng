#pragma once

#include <renderer/vertex/VertexSemantic.hpp>

namespace libng {

struct VertexBase {
  using Semantic = VertexSemantic;

  using PosType    = void;
  using ColorType  = void;
  using UvType     = void;
  using NormalType = void;
};

}; // namespace libng