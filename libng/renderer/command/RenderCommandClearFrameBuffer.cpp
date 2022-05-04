#include <renderer/command/RenderCommandClearFrameBuffer.hpp>

namespace libng {

RenderCommandClearFrameBuffer::RenderCommandClearFrameBuffer()
  : Base(Type::ClearFrameBuffers) {
}

RenderCommandClearFrameBuffer::~RenderCommandClearFrameBuffer() {
}

RenderCommandClearFrameBuffer& RenderCommandClearFrameBuffer::setColor(const Color4f& color_) {
  color = color_;
  return *this;
}

RenderCommandClearFrameBuffer& RenderCommandClearFrameBuffer::setDepth(const float depth_) {
  depth = depth_;
  return *this;
}

RenderCommandClearFrameBuffer& RenderCommandClearFrameBuffer::dontClearColor() {
  color.reset();
  return *this;
}

RenderCommandClearFrameBuffer& RenderCommandClearFrameBuffer::dontClearDepth() {
  depth.reset();
  return *this;
}

} // namespace libng