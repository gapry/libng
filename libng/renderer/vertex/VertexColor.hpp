#pragma once

#include <renderer/vertex/VertexType.hpp>
#include <renderer/vertex/VertexBase.hpp>
#include <renderer/vertex/VertexTypeUtil.hpp>
#include <renderer/type/RenderDataType.hpp>
#include <renderer/type/RenderDataTypeUtil.hpp>

namespace libng {

template<class COLOR_TYPE, u8 COLOR_COUNT, class BASE> // Issue
struct VertexColor : public BASE {                     // Issue
  using ColorType = COLOR_TYPE;

  ColorType color[COLOR_COUNT]; // Issue

  static const RenderDataType kColorType = RenderDataTypeUtil::get<ColorType>();
  static const u8 kColorCount            = COLOR_COUNT;
  static const VertexType kType          = VertexTypeUtil::addColor(BASE::kType, kColorType, kColorCount);

  static const VertexLayout* layout() {
    static const VertexLayout* s = VertexLayoutManager::current()->getLayout(VertexPosColorUv::kType);
    return s;
  }

  static void onRegister(VertexLayout* layout) {
    BASE::onRegister(layout);
    layout->addElement(Semantic::Color0, &VertexColor::color);
  }
};

} // namespace libng