#pragma once

#include <renderer/command/RenderCommandType.hpp>
#include <renderer/command/RenderCommand.hpp>

namespace libng {

class RenderCommandSwapBuffer : public RenderCommand {
  using Base = RenderCommand;

public:
  RenderCommandSwapBuffer();

  ~RenderCommandSwapBuffer();
};

} // namespace libng