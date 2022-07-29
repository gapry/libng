#include <libng_render/buffer/RenderCommandBuffer.hpp>

namespace libng {

RenderCommandClearFrameBuffer* RenderCommandBuffer::clearFrameBuffer() {
  return newCommand<RenderCommandClearFrameBuffer>();
}

RenderCommandSwapBuffer* RenderCommandBuffer::swapBuffers() {
  return newCommand<RenderCommandSwapBuffer>();
}

void RenderCommandBuffer::drawMesh(const SrcLoc& debugLoc, const RenderMesh& mesh, Material* material) {
  for (auto& sm : mesh.subMeshes()) {
    drawSubMesh(debugLoc, sm, material);
  }
}

void RenderCommandBuffer::drawSubMesh(const SrcLoc& debugLoc, const RenderSubMesh& subMesh, Material* material) {
  if (!material) {
    LIBNG_ASSERT(false);
    return;
  }

  auto passes = material->passes();

  for (size_t i = 0; i < passes.size(); i++) {
    auto* cmd = newCommand<RenderCommandDrawCall>();
#if _DEBUG
    cmd->debugLoc = debugLoc;
#endif
    cmd->material          = material;
    cmd->materialPassIndex = i;

    cmd->primitive    = subMesh.primitive();
    cmd->vertexLayout = subMesh.vertexLayout();
    cmd->vertexBuffer = subMesh.vertexBuffer();
    cmd->vertexCount  = subMesh.vertexCount();
    cmd->indexBuffer  = subMesh.indexBuffer();
    cmd->indexType    = subMesh.indexType();
    cmd->indexCount   = subMesh.indexCount();
  }
}

void RenderCommandBuffer::reset() {
  _allocator.clear();
  for (auto* cmd : _commands) {
    cmd->~RenderCommand();
  }
  _commands.clear();
}

Span<RenderCommand*> RenderCommandBuffer::commands() {
  return _commands;
}

} // namespace libng