#pragma once

#include <libng_core/memory/SPtr.hpp>
#include <libng_render/buffer/GPUBuffer.hpp>
#include <libng_render/command/RenderCommand.hpp>
#include <libng_render/type/RenderDataType.hpp>
#include <libng_render/type/RenderPrimitiveType.hpp>
#include <libng_render/vertex/VertexLayout.hpp>

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