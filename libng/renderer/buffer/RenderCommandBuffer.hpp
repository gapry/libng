#pragma once

#include <types/noncopyable.hpp>
#include <memory/allocator/LinearAllocator.hpp>
#include <memory/util.hpp>
#include <debug/SourceLocation.hpp>

#include <renderer/command/RenderCommand.hpp>
#include <renderer/command/RenderCommandClearFrameBuffer.hpp>
#include <renderer/command/RenderCommandSwapBuffer.hpp>
#include <renderer/command/RenderCommandDrawCall.hpp>
#include <renderer/mesh/RenderMesh.hpp>
#include <renderer/mesh/RenderSubMesh.hpp>

namespace libng {

class RenderCommandBuffer : public NonCopyable {
public:
  RenderCommandClearFrameBuffer* clearFrameBuffer();

  RenderCommandSwapBuffer* swapBuffers();

  void drawMesh(const SrcLoc& debugLoc, const RenderMesh& mesh);

  void drawSubMesh(const SrcLoc& debugLoc, const RenderSubMesh& subMesh);

  void reset();

  Span<RenderCommand*> commands();

  template<class CMD>
  CMD* newCommand();

private:
  Vector_<RenderCommand*, 64> _commands;

  LinearAllocator _allocator;
};

template<class CMD>
CMD* RenderCommandBuffer::newCommand() {
  auto* buff = _allocator.allocate(sizeof(CMD));
  auto* cmd  = new (buff) CMD();
  _commands.emplace_back(cmd);
  return cmd;
}

} // namespace libng