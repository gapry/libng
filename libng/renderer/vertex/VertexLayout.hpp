#pragma once

#include <types/noncopyable.hpp>
#include <types/number.hpp>
#include <renderer/type/RenderDataType.hpp>
#include <renderer/vertex/VertexSemantic.hpp>

namespace libng {

struct VertexLayout : public NonCopyable {
  using Semantic = VertexSemantic;
  using DataType = RenderDataType;

  struct Element {
    Semantic semantic = Semantic::None;
    DataType dataType = DataType::None;
    u16 offset        = 0;
  };
};

} // namespace libng