#pragma once

#include <libng_render/type/RenderDataType.hpp>
#include <libng_render/type/RenderDataTypeUtil.hpp>
#include <libng_render/vertex/VertexBase.hpp>
#include <libng_render/vertex/VertexLayout.hpp>
#include <libng_render/vertex/VertexType.hpp>
#include <libng_render/vertex/VertexTypeUtil.hpp>

namespace libng {

template<class BINORMAL_TYPE, u8 BINORMAL_COUNT, class BASE> // Issue
struct VertexBinormal : public BASE {                        // Issue
  using BinormalType = BINORMAL_TYPE;

  BinormalType binormal[BINORMAL_COUNT];

  static const RenderDataType kBinormalType = RenderDataTypeUtil::get<BinormalType>();
  static const u8 kBinormalCount            = BINORMAL_COUNT;
  static const VertexType kType             = VertexTypeUtil::addBinormal(BASE::kType, kBinormalCount);

  static const VertexLayout* layout() {
    static const VertexLayout* s = VertexLayoutManager::current()->getLayout(VertexPosColorUv::kType);
    return s;
  }

  static void onRegister(VertexLayout* layout) {
    static_assert(std::is_same<BinormalType, NormalType>::value, ""); // Issue
    BASE::onRegister(layout);
    layout->addElement(Semantic::BINORMAL, &VertexBinormal::binormal);
  }
};

} // namespace libng