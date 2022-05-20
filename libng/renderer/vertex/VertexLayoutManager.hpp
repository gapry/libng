#pragma once

#include <libcxx/util/util.hpp>

#include <renderer/vertex/VertexLayout.hpp>
#include <renderer/vertex/VertexType.hpp>
#include <renderer/vertex/VertexCommon.hpp>

namespace libng {

class VertexLayoutManager {
public:
  VertexLayoutManager();

  static VertexLayoutManager* current();

  const VertexLayout* getLayout(VertexType type);

  template<class VERTEX>
  void registerLayout(void) {
    VertexLayout* layout = _createLayout(VERTEX::kType);
    layout->stride       = sizeof(VERTEX);
    layout->type         = VERTEX::kType;
    VERTEX::onRegister(layout);
  }

private:
  VertexLayout* _createLayout(VertexType type); // Issue

  static VertexLayoutManager* s_current;
  Map<VertexType, VertexLayout> _table;
};

} // namespace libng
