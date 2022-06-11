#include <libng_render/command/RenderCommandSwapBuffer.hpp>

namespace libng {

RenderCommandSwapBuffer::RenderCommandSwapBuffer()
  : Base(Type::SwapBuffer) {
}

RenderCommandSwapBuffer::~RenderCommandSwapBuffer() {
}

} // namespace libng