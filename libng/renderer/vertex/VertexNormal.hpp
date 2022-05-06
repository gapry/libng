#pragma once

#include <renderer/vertex/VertexType.hpp>
#include <renderer/vertex/VertexBase.hpp>
#include <renderer/vertex/VertexTypeUtil.hpp>
#include <renderer/type/RenderDataType.hpp>
#include <renderer/type/RenderDataTypeUtil.hpp>

namespace libng {

template<class NORMAL_TYPE, u8 NORMAL_COUNT, class BASE> // Issue
struct VertexNormal : public BASE {                      // Issue
  using NormalType = NORMAL_TYPE;

  NormalType normal[NORMAL_COUNT]; // Issue

  static const RenderDataType kNormalType = RenderDataTypeUtil::get<NormalType>();
  static const u8 kNormalCount            = NORMAL_COUNT;
  static const VertexType kType           = VertexTypeUtil::addNormal(BASE::kType, kNormalType, kNormalCount);

  static const VertexLayout* layout() {
    static const VertexLayout* s = VertexLayoutManager::current()->getLayout(VertexPosColorUv::kType);
    return s;
  }

  static void onRegister(VertexLayout* layout) {
    BASE::onRegister(layout);
    layout->addElement(Semantic::Normal, &VertexNormal::normal);
  }
};

} // namespace libng