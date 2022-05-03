#pragma once

#include <renderer/mesh/EditMesh.hpp>

namespace libng {

class RenderSubMesh {
public:
  void create(const EditMesh& srcMesh);
};

}