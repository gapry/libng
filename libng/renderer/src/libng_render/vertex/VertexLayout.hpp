#pragma once

#include <type_traits>
#include <libng_core/types/noncopyable.hpp>
#include <libng_core/types/number.hpp>
#include <libng_core/memory/util.hpp>
#include <libng_core/libcxx/fixed_vector.hpp>
#include <libng_render/type/RenderDataType.hpp>
#include <libng_render/type/RenderDataTypeUtil.hpp>
#include <libng_render/vertex/VertexType.hpp>
#include <libng_render/vertex/VertexSemantic.hpp>

namespace libng {

struct VertexLayout : public NonCopyable {
  using Semantic = VertexSemantic;
  using DataType = RenderDataType;

  struct Element {
    Semantic semantic = Semantic::None;
    DataType dataType = DataType::None;
    u16 offset        = 0;
  };

  VertexType type = VertexType::None;
  size_t stride   = 0;

  Vector_<Element, 16> elements;

  template<class VERTEX, class ATTR>
  void addElement(Semantic semantic, ATTR VERTEX::*attr, size_t index = 0) {
    if (std::is_array<ATTR>()) {      // Issue:
      size_t n = std::extent<ATTR>(); // Issue:
      for (size_t i = 0; i < n; i++) {
        _addElement(semantic + static_cast<int>(i), attr, i);
      }
    } else {
      _addElement(semantic, attr, 0);
    }
  }

private:
  template<class VERTEX, class ATTR>
  void _addElement(Semantic semantic, ATTR VERTEX::*attr, size_t index) {
    auto& o    = elements.push_back();
    o.semantic = semantic;

    using A    = std::remove_extent<ATTR>::type; // Issue:
    o.dataType = RenderDataTypeUtil::get<A>();   // Issue:
    o.offset   = static_cast<u16>(memberOffset(attr) + sizeof(A) * index);
  }
};

} // namespace libng
