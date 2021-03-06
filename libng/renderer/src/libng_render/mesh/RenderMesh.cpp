#include <libng_core/math/Color/Color.hpp>
#include <libng_core/math/Tuple/Tuple2.hpp>
#include <libng_core/math/Tuple/Tuple3.hpp>

#include <libng_render/mesh/RenderMesh.hpp>
#include <libng_render/mesh/RenderMeshInternalHelper.hpp>
#include <libng_render/type/RenderDataTypeUtil.hpp>
#include <libng_render/type/RenderPrimitiveType.hpp>
#include <libng_render/vertex/VertexLayoutManager.hpp>
#include <libng_render/vertex/VertexTypeUtil.hpp>

namespace libng {

void RenderMesh::create(const EditMesh& src) {
  using Helper = RenderMeshInternalHelper;
  clear();

  u8 uvCount       = 0;
  u8 colorCount    = 0;
  u8 normalCount   = 0;
  u8 tangentCount  = 0;
  u8 binormalCount = 0;

  _primitive = RenderPrimitiveType::Triangles;

  size_t vertexCount = src.pos.size();
  if (vertexCount <= 0) {
    return;
  }

  // clang-format off
	if (Helper::hasAttr(src.color.size(),    vertexCount)) colorCount = 1;
	if (Helper::hasAttr(src.normal.size(),   vertexCount)) normalCount = 1;
	if (Helper::hasAttr(src.tangent.size(),  vertexCount)) tangentCount = 1;
	if (Helper::hasAttr(src.binormal.size(), vertexCount)) binormalCount = 1;
  // clang-format on

  for (u8 i = 0; i < EditMesh::kUvCountMax; i++) {
    if (Helper::hasAttr(src.uv[i].size(), vertexCount))
      uvCount = i + 1;
  }

  // clang-format off
  //
  // Issue: a nonstatic member reference must be relative to a specific objectC/C++(245)
  //
	auto vertexType = VertexTypeUtil::make(RenderDataTypeUtil::get<Tuple3f>(), 
						                             RenderDataTypeUtil::get<Color4b>(), colorCount, 
						                             RenderDataTypeUtil::get<Tuple2f>(), uvCount,
						                             RenderDataTypeUtil::get<Tuple3f>(), normalCount, tangentCount, binormalCount);
  // clang-format on

  _vertexLayout = VertexLayoutManager::current()->getLayout(vertexType);

  if (!_vertexLayout) {
    throw LIBNG_ERROR("cannot find vertex Layout for mesh");
  }

  setSubMeshCount(1); // Issue
  _subMeshes[0].create(src);
}

void RenderMesh::clear() {
  _vertexLayout = nullptr;
  _subMeshes.clear();
}

Span<RenderSubMesh> RenderMesh::subMeshes() {
  return _subMeshes;
}

Span<const RenderSubMesh> RenderMesh::subMeshes() const {
  return _subMeshes;
}

RenderPrimitiveType RenderMesh::primitive() const {
  return _primitive;
}

const VertexLayout* RenderMesh::vertexLayout() const {
  return _vertexLayout;
}

void RenderMesh::setSubMeshCount(size_t newSize) {
  size_t oldSize = _subMeshes.size();
  _subMeshes.resize(newSize);
  for (size_t i = oldSize; i < newSize; i++) {
    _subMeshes[i]._mesh = this;
  }
}

} // namespace libng