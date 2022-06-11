#pragma once

#include <libng_render/command/RenderCommandType.hpp>
#include <libng_render/command/RenderCommand.hpp>

namespace libng {

class RenderCommandSwapBuffer : public RenderCommand {
  using Base = RenderCommand;

public:
  RenderCommandSwapBuffer();

  ~RenderCommandSwapBuffer();
};

} // namespace libng