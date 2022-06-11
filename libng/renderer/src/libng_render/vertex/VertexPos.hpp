#pragma once

#include <libng_render/vertex/VertexType.hpp>
#include <libng_render/vertex/VertexBase.hpp>
#include <libng_render/vertex/VertexTypeUtil.hpp>
#include <libng_render/vertex/VertexLayout.hpp>
#include <libng_render/vertex/VertexLayoutManager.hpp>
#include <libng_render/type/RenderDataType.hpp>
#include <libng_render/type/RenderDataTypeUtil.hpp>

namespace libng {

template<class POS_TYPE>
struct VertexPos : public VertexBase {
  using PosType = POS_TYPE;

  PosType pos; // Issue

  static const RenderDataType kPosType = RenderDataTypeUtil::get<PosType>();
  static const VertexType kType        = VertexTypeUtil::addPos(VertexType::None, kPosType);

  /**
   * In C++, we can't assign the value directly, static const T* v = x;
   */
  static const VertexLayout* layout() {
    static const VertexLayout* s = VertexLayoutManager::current()->getLayout(VertexPosColorUv::kType);
    return s;
  }

  static void onRegister(VertexLayout* layout) {
    layout->addElement(Semantic::Pos, &VertexPos::pos);
  }
};

} // namespace libng