#include <renderer/command/RenderCommandSwapBuffer.hpp>

namespace libng {

RenderCommandSwapBuffer::RenderCommandSwapBuffer()
  : Base(Type::SwapBuffers) {
}

RenderCommandSwapBuffer::~RenderCommandSwapBuffer() {
}

} // namespace libng