#include <renderer/mesh/RenderMesh.hpp>
#include <renderer/mesh/RenderSubMesh.hpp>

namespace libng {

void RenderSubMesh::create(const EditMesh& srcMesh) {
}

void RenderSubMesh::clear() {
}

GPUBuffer* RenderSubMesh::vertexBuffer() const {
  return constCast(_vertexBuffer);
}

GPUBuffer* RenderSubMesh::indextBuffer() const {
  return constCast(_indexBuffer);
}

size_t RenderSubMesh::vertexCount() const {
  return _vertexCount;
}

size_t RenderSubMesh::indexCount() const {
  return _indexCount;
}

RenderDataType RenderSubMesh::indexType() const {
  return _indexType;
}

LIBNG_INLINE RenderPrimitiveType RenderSubMesh::primitiveType() const {
  return _mesh->primitiveType();
}

LIBNG_INLINE const VertexLayout* RenderSubMesh::vertexLayout() const {
  return _mesh->vertexLayout();
}

} // namespace libng