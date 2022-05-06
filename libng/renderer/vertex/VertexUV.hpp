#pragma once

#include <renderer/vertex/VertexType.hpp>
#include <renderer/vertex/VertexBase.hpp>
#include <renderer/vertex/VertexTypeUtil.hpp>
#include <renderer/type/RenderDataType.hpp>
#include <renderer/type/RenderDataTypeUtil.hpp>

namespace libng {

template<class UV_TYPE, u8 UV_COUNT, class BASE> // Issue
struct VertexUV : public BASE {                  // Issue
  using UVType = UV_TYPE;

  UVType uv[UV_COUNT]; // Issue

  static const RenderDataType kUvType = RenderDataTypeUtil::get<UVType>();
  static const u8 kUvCount            = UV_COUNT;
  static const VertexType kType       = VertexTypeUtil::addUv(BASE::kType, kUvType, kUvCount);

  static const VertexLayout* layout() {
    static const VertexLayout* s = VertexLayoutManager::current()->getLayout(VertexPosColorUv::kType);
    return s;
  }

  static void onRegister(VertexLayout* layout) {
    BASE::onRegister(layout);
    layout->addElement(Semantic::TexCoord0, &VertexUV::uv);
  }
};

} // namespace libng