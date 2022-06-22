#pragma once

#include <libng_render/command/RenderCommand.hpp>
#include <libng_render/command/RenderCommandType.hpp>

namespace libng {

class RenderCommandSwapBuffer : public RenderCommand {
  using Base = RenderCommand;

public:
  RenderCommandSwapBuffer();

  ~RenderCommandSwapBuffer();
};

} // namespace libng