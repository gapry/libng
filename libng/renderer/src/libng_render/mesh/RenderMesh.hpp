#pragma once

#include <libng_core/libcxx/fixed_vector.hpp>
#include <libng_core/libcxx/span.hpp>
#include <libng_render/mesh/EditMesh.hpp>
#include <libng_render/mesh/RenderSubMesh.hpp>
#include <libng_render/type/RenderPrimitiveType.hpp>
#include <libng_render/vertex/VertexLayout.hpp>

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
