#pragma once

#include <libng_core/memory/SPtr.hpp>
#include <libng_core/types/function.hpp>
#include <libng_core/types/utility.hpp>
#include <libng_render/buffer/GPUBuffer.hpp>
#include <libng_render/mesh/EditMesh.hpp>
#include <libng_render/type/RenderDataType.hpp>
#include <libng_render/type/RenderPrimitiveType.hpp>
#include <libng_render/vertex/VertexLayout.hpp>

namespace libng {

class RenderMesh;

class RenderSubMesh {
  friend class RenderMesh;

public:
  void create(const EditMesh& srcMesh);

  void clear();

  GPUBuffer* vertexBuffer() const;

  GPUBuffer* indexBuffer() const;

  size_t vertexCount() const;

  size_t indexCount() const;

  RenderDataType indexType() const;

  RenderPrimitiveType primitive() const;

  const VertexLayout* vertexLayout() const;

protected:
  RenderMesh* _mesh = nullptr;

  RenderDataType _indexType = RenderDataType::None;

  SPtr<GPUBuffer> _vertexBuffer;
  SPtr<GPUBuffer> _indexBuffer;

  size_t _vertexCount = 0;
  size_t _indexCount  = 0;
};

} // namespace libng