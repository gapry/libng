#pragma once

#include <mm/SPtr.hpp>
#include <types/function.hpp>
#include <types/utility.hpp>

#include <renderer/vertex/VertexLayout.hpp>
#include <renderer/type/RenderPrimitiveType.hpp>
#include <renderer/type/RenderDataType.hpp>
#include <renderer/buffer/GPUBuffer.hpp>
#include <renderer/mesh/EditMesh.hpp>

namespace libng {

class RenderMesh;

class RenderSubMesh {
  friend class RenderMesh;

public:
  void create(const EditMesh& srcMesh);

  void clear();

  GPUBuffer* vertexBuffer() const;

  GPUBuffer* indextBuffer() const;

  size_t vertexCount() const;

  size_t indexCount() const;

  RenderDataType indexType() const;

  RenderPrimitiveType primitiveType() const;

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