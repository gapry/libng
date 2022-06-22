#pragma once

#include <libng_core/libcxx/map.hpp>
#include <libng_render/vertex/VertexCommon.hpp>
#include <libng_render/vertex/VertexLayout.hpp>
#include <libng_render/vertex/VertexType.hpp>

namespace libng {

class VertexLayoutManager {
public:
  VertexLayoutManager();

  static VertexLayoutManager* current();

  const VertexLayout* getLayout(VertexType type);

  template<class VERTEX>
  void registerLayout(void) {
    VertexLayout* layout = _createLayout(VERTEX::kType);
    layout->stride       = sizeof(VERTEX); // Issue
    layout->type         = VERTEX::kType;
    VERTEX::onRegister(layout);
  }

private:
  VertexLayout* _createLayout(VertexType type); // Issue

  static VertexLayoutManager* s_current;
  Map<VertexType, VertexLayout> _table;
};

} // namespace libng
