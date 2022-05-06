#include <renderer/mesh/EditMesh.hpp>

namespace libng {

void EditMesh::clear() {
  indices.clear();

  pos.clear();

  for (auto& t : uv) {
    t.clear();
  }

  color.clear();
  normal.clear();
  tangent.clear();
  binormal.clear();
}

} // namespace libng