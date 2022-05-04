#pragma once

#include <mm/SPtr.hpp>

#include <renderer/vertex/VertexLayout.hpp>
#include <renderer/buffer/GPUBuffer.hpp>
#include <renderer/command/RenderCommand.hpp>
#include <renderer/type/RenderDataType.hpp>
#include <renderer/type/RenderPrimitiveType.hpp>

namespace libng {

class RenderCommandDrawCall : public RenderCommand {
  using Base = RenderCommand;

public:
  RenderCommandDrawCall()
    : Base(Type::DrawCall) {
  }

  RenderPrimitiveType primitive    = RenderPrimitiveType::None;
  const VertexLayout* vertexLayout = nullptr;
  RenderDataType indexType         = RenderDataType::UInt16;

  SPtr<GPUBuffer> vertexBuffer;
  SPtr<GPUBuffer> indexBuffer;

  size_t vertexCount = 0;
  size_t indexCount  = 0;
};

} // namespace libng