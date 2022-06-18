#pragma once

#include <libng_render/vertex/VertexType.hpp>
#include <libng_render/vertex/VertexBase.hpp>
#include <libng_render/vertex/VertexTypeUtil.hpp>
#include <libng_render/type/RenderDataType.hpp>
#include <libng_render/type/RenderDataTypeUtil.hpp>

namespace libng {

template<class TANGENT_TYPE, u8 TANGENT_COUNT, class BASE>
struct VertexTangent : public BASE {
  using TangentType = TANGENT_TYPE;

  TangentType tangent[TANGENT_COUNT]; // Issue

  static const RenderDataType kTangentType = RenderDataTypeUtil::get<TangentType>();
  static const u8 kTangentCount            = TANGENT_COUNT;
  static const VertexType kType            = VertexTypeUtil::addTangent(BASE::kType, kTangentCount);

  static const VertexLayout* layout() {
    static const VertexLayout* s = VertexLayoutManager::current()->getLayout(VertexPosColorUv::kType);
    return s;
  }

  static void onRegister(VertexLayout* layout) {
    static_assert(std::is_same<TangentType, NormalType>::value, ""); // Issue
    BASE::onRegister(layout);
    layout->addElement(Semantic::TANGENT, &VertexTangent::tangent);
  }
};

} // namespace libng