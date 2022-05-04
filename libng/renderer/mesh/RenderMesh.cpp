#include <renderer/mesh/RenderMesh.hpp>

namespace libng {

void RenderMesh::create(const EditMesh& src) {
}

Span<RenderSubMesh> RenderMesh::subMeshes() {
  return _subMeshes;
}

Span<const RenderSubMesh> RenderMesh::subMeshes() const {
  return _subMeshes;
}

RenderPrimitiveType RenderMesh::primitiveType() const {
  return _primitiveType;
}

const VertexLayout* RenderMesh::vertexLayout() const {
  return _vertexLayout;
}

} // namespace libng