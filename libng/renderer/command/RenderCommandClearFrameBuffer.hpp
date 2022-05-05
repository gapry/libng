#pragma once

#include <math/Color.hpp>

#include <libcxx/util.hpp>

#include <renderer/command/RenderCommand.hpp>
#include <renderer/command/RenderCommandClearFrameBuffer.hpp>

namespace libng {

class RenderCommandClearFrameBuffer : public RenderCommand {
  using Base = RenderCommand;
  using This = RenderCommandClearFrameBuffer;

public:
  RenderCommandClearFrameBuffer();

  ~RenderCommandClearFrameBuffer();

  This& setColor(const Color4f& color_);

  This& setDepth(const float depth_);

  This& dontClearColor();

  This& dontClearDepth();

  Opt<Color4f> color = Color4f(1.0f, 1.0f, 1.0f, 1.0f);
  Opt<float> depth   = 0;
};

} // namespace libng