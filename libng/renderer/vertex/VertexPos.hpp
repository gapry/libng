#pragma once

#include <renderer/vertex/VertexType.hpp>
#include <renderer/vertex/VertexBase.hpp>
#include <renderer/vertex/VertexTypeUtil.hpp>
#include <renderer/type/RenderDataType.hpp>
#include <renderer/type/RenderDataTypeUtil.hpp>

namespace libng {

template<class POS_TYPE>
struct VertexPos : public VertexBase {
  using PosType = POS_TYPE;

  PosType pos; // Issue

  static const RenderDataType kPosType = RenderDataTypeUtil::get<PosType>();
  static const VertexType kType        = VertexTypeUtil::addPos(VertexType::None, kPosType);

  static const VertexLayout* layout() {
    static const VertexLayout* s = VertexLayoutManager::current()->getLayout(VertexPosColorUv::kType);
    return s;
  }

  static void onRegister(VertexLayout* layout) {
    layout->addElement(Semantic::Pos, &VertexPos::pos);
  }
};

} // namespace libng