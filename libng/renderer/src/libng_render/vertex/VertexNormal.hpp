#pragma once

#include <libng_render/type/RenderDataType.hpp>
#include <libng_render/type/RenderDataTypeUtil.hpp>
#include <libng_render/vertex/VertexBase.hpp>
#include <libng_render/vertex/VertexLayout.hpp>
#include <libng_render/vertex/VertexLayoutManager.hpp>
#include <libng_render/vertex/VertexType.hpp>
#include <libng_render/vertex/VertexTypeUtil.hpp>

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
    layout->addElement(Semantic::NORMAL, &VertexNormal::normal);
  }
};

} // namespace libng