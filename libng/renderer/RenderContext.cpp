#include <renderer/RenderContext.hpp>

namespace libng {

/**
 * @brief Construct a new RenderContext object
 *
 * Issue:
 * @code
 *   RenderContext(CreateDesc& desc) = default;
 * @endcode
 *
 * @param desc
 */
RenderContext::RenderContext(RenderContext::CreateDesc& desc) {
}

/**
 * @brief public member function
 *
 * call the protected virtual function
 */
void RenderContext::beginRender() {
  onBeginRender();
}

/**
 * @brief public member function
 *
 * call the protected virtual function
 */
void RenderContext::endRender() {
  onEndRender();
}

/**
 * @brief public member function
 *
 * call the protected virtual function
 */
void RenderContext::commit(RenderCommandBuffer& cmdBuff) {
  onCommit(cmdBuff);
}

/**
 * @brief public member function
 *
 * 1. avoid the redundant assignment
 * 2. call the protected virtual function
 */
void RenderContext::setFrameBufferSize(Vec2f newSize) {
  if (_frameBufferSize == newSize) {
    return;
  }
  _frameBufferSize = newSize;
  onSetFrameBufferSize(newSize);
}

} // namespace libng