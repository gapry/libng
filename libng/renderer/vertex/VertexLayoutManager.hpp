#pragma once

#include <renderer/vertex/VertexLayout.hpp>

namespace libng {

class VertexLayoutManager {
public:
  VertexLayoutManager();

private:
  static VertexLayoutManager* s_current;
};

} // namespace libng
