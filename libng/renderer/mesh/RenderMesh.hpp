#pragma once

#include <third_party/eastl/eastl.hpp>

#include <renderer/vertex/VertexLayout.hpp>
#include <renderer/type/RenderPrimitiveType.hpp>
#include <renderer/mesh/EditMesh.hpp>
#include <renderer/mesh/RenderSubMesh.hpp>

namespace libng {

class RenderMesh {
public:
  void create(const EditMesh& src);

  RenderPrimitiveType primitiveType() const;

  const VertexLayout* vertexLayout() const;

  Span<RenderSubMesh> subMeshes();

  Span<const RenderSubMesh> subMeshes() const;

private:
  RenderPrimitiveType _primitiveType = RenderPrimitiveType::Triangles;
  const VertexLayout* _vertexLayout  = nullptr;
  Vector_<RenderSubMesh, 1> _subMeshes;
};

} // namespace libng