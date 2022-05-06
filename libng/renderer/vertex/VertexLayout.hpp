#pragma once

// std
#include <type_traits>

// libng
#include <types/noncopyable.hpp>
#include <types/number.hpp>

#include <memory/utility.hpp>

#include <libcxx/util.hpp>

#include <renderer/type/RenderDataType.hpp>
#include <renderer/type/RenderDataTypeUtil.hpp>
#include <renderer/vertex/VertexType.hpp>
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