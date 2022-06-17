#pragma once

#include <libng_core/types/noncopyable.hpp>
#include <libng_core/memory/allocator/LinearAllocator.hpp>
#include <libng_core/memory/util.hpp>
#include <libng_core/debug/SourceLocation.hpp>
#include <libng_render/command/RenderCommand.hpp>
#include <libng_render/command/RenderCommandClearFrameBuffer.hpp>
#include <libng_render/command/RenderCommandSwapBuffer.hpp>
#include <libng_render/command/RenderCommandDrawCall.hpp>
#include <libng_render/mesh/RenderMesh.hpp>
#include <libng_render/mesh/RenderSubMesh.hpp>

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