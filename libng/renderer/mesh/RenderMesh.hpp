#pragma once

#include <libcxx/util/util.hpp>

#include <renderer/vertex/VertexLayout.hpp>
#include <renderer/type/RenderPrimitiveType.hpp>
#include <renderer/mesh/EditMesh.hpp>
#include <renderer/mesh/RenderSubMesh.hpp>

namespace libng {

class RenderMesh {
public:
  void create(const EditMesh& src);

  void clear();

  RenderPrimitiveType primitive() const;

  const VertexLayout* vertexLayout() const;

  Span<RenderSubMesh> subMeshes();

  Span<const RenderSubMesh> subMeshes() const;

  void setSubMeshCount(size_t newSize);

private:
  RenderPrimitiveType _primitive    = RenderPrimitiveType::Triangles;
  const VertexLayout* _vertexLayout = nullptr;
  Vector_<RenderSubMesh, 1> _subMeshes;
};

} // namespace libng
