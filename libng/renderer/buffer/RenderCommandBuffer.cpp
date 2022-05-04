#include <renderer/buffer/RenderCommandBuffer.hpp>

namespace libng {

RenderCommandClearFrameBuffer* RenderCommandBuffer::clearFrameBuffer() {
  return newCommand<RenderCommandClearFrameBuffer>();
}

RenderCommandSwapBuffer* RenderCommandBuffer::swapBuffers() {
  return newCommand<RenderCommandSwapBuffer>();
}

void RenderCommandBuffer::drawMesh(const SrcLoc& debugLoc, const RenderMesh& mesh) {
  for (auto& sm : mesh.subMeshes()) {
    drawSubMesh(debugLoc, sm);
  }
}

void RenderCommandBuffer::drawSubMesh(const SrcLoc& debugLoc, const RenderSubMesh& subMesh) {
  auto* cmd         = newCommand<RenderCommandDrawCall>();
  cmd->debugLoc     = debugLoc;
  cmd->primitive    = subMesh.primitiveType();
  cmd->vertexLayout = subMesh.vertexLayout();
  cmd->vertexBuffer = subMesh.vertexBuffer();
  cmd->vertexCount  = subMesh.vertexCount();
  cmd->indexBuffer  = subMesh.indextBuffer();
  cmd->indexType    = subMesh.indexType();
  cmd->indexCount   = subMesh.indexCount();
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