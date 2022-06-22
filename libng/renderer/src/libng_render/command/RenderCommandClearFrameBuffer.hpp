#pragma once

#include <libng_core/libcxx/optional.hpp>
#include <libng_core/math/Color.hpp>
#include <libng_render/command/RenderCommand.hpp>
#include <libng_render/command/RenderCommandClearFrameBuffer.hpp>

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
