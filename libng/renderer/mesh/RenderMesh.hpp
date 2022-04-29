#pragma once

#include <renderer/mesh/EditMesh.hpp>

namespace libng {

class RenderMesh {
public:
  void create(const EditMesh& src);
};

} // namespace libng