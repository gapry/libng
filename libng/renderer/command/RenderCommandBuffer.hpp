#pragma once

#include <types/noncopyable.hpp>
#include <mm/LinearAllocator.hpp>
#include <third_party/eastl/eastl.hpp>
#include <renderer/command/RenderCommand.hpp>
#include <renderer/mesh/RenderMesh.hpp>

namespace libng {

class RenderCommandBuffer : public NonCopyable {
public:
  void drawMesh(RenderMesh& mesh);

  void commands();

private:
  Vector_<RenderCommand*, 64> _commands;
  LinearAllocator _allocator;
};

} // namespace libng