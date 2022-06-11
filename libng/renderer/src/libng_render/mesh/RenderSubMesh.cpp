#include <libng_render/Renderer.hpp>
#include <libng_render/mesh/RenderMesh.hpp>
#include <libng_render/mesh/RenderSubMesh.hpp>
#include <libng_render/mesh/RenderMeshInternalHelper.hpp>
#include <libng_render/buffer/GPUBuffer.hpp>
#include <libng_render/buffer/GPUBufferType.hpp>
#include <libng_render/vertex/VertexSemantic.hpp>
#include <libng_render/vertex/VertexSemanticType.hpp>

namespace libng {

void RenderSubMesh::create(const EditMesh& src) {
  using Helper = RenderMeshInternalHelper;

  clear();

  _vertexCount = src.pos.size();
  _indexCount  = src.indices.size();

  if (_vertexCount <= 0) {
    return;
  }

  auto* vertexLayout = _mesh->vertexLayout();

  Vector_<u8, 1024> vertexData;
  vertexData.resize(vertexLayout->stride * _vertexCount);

  auto* pData = vertexData.data();
  auto stride = vertexLayout->stride;
  auto vc     = _vertexCount;

  for (auto& e : vertexLayout->elements) {
    using S  = VertexSemantic;
    using ST = VertexSemanticType;
    using U  = VertexSemanticUtil;

    auto semanticType  = U::getType(e.semantic);
    auto semanticIndex = U::getIndex(e.semantic);

    switch (semanticType) {
      case ST::TexCoord: {
        if (semanticIndex < EditMesh::kUvCountMax) {
          Helper::copyVertexData(pData, vc, e, stride, src.uv[semanticIndex].data());
          break;
        }
        continue;
      } break;
    }

    // clang-format off
		switch (e.semantic) {
			case S::Pos:		  Helper::copyVertexData(pData, vc, e, stride, src.pos.data());      break;
			case S::Color0:		Helper::copyVertexData(pData, vc, e, stride, src.color.data());    break;
			case S::Normal:		Helper::copyVertexData(pData, vc, e, stride, src.normal.data());   break;
			case S::Tangent:	Helper::copyVertexData(pData, vc, e, stride, src.tangent.data());  break;
			case S::Binormal:	Helper::copyVertexData(pData, vc, e, stride, src.binormal.data()); break;
		}
    // clang-format on
  }

  auto* renderer = Renderer::current();

  //
  {
    GPUBuffer::CreateDesc desc;
    desc.type       = GPUBufferType::Vertex;
    desc.bufferSize = _vertexCount * vertexLayout->stride;
    _vertexBuffer   = renderer->createGPUBuffer(desc);
    _vertexBuffer->uploadToGPU(vertexData);
  }

  if (_indexCount > 0) {
    Span<const u8> indexData;
    Vector_<u16, 1024> index16Data;

    if (_vertexCount > UINT16_MAX) {
      _indexType = RenderDataType::UInt32;
      indexData  = spanCast<const u8, const u32>(src.indices);
    } else {
      _indexType = RenderDataType::UInt16;
      index16Data.resize(src.indices.size());
      for (size_t i = 0; i < src.indices.size(); i++) {
        u32 vi         = src.indices[i];
        index16Data[i] = static_cast<u16>(vi);
      }
      indexData = spanCast<const u8, const u16>(index16Data);
    }

    GPUBuffer::CreateDesc desc;
    desc.type       = GPUBufferType::Index;
    desc.bufferSize = indexData.size();
    _indexBuffer    = renderer->createGPUBuffer(desc);
    _indexBuffer->uploadToGPU(indexData);
  }
}

void RenderSubMesh::clear() {
  _vertexBuffer = nullptr;
  _indexBuffer  = nullptr;
  _vertexCount  = 0;
  _indexCount   = 0;
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

RenderPrimitiveType RenderSubMesh::primitive() const {
  return _mesh->primitive();
}

const VertexLayout* RenderSubMesh::vertexLayout() const {
  return _mesh->vertexLayout();
}

} // namespace libng
