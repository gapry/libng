#pragma once

#include <libng_core/math/Vector/Vec2.hpp>
#include <libng_core/types/Object.hpp>
#include <libng_render/RenderContextCreateDesc.hpp>
#include <libng_render/buffer/RenderCommandBuffer.hpp>
#include <libng_render/command/RenderCommandType.hpp>

namespace libng {

class RenderContext : public Object {
public:
  using CreateDesc = RenderContextCreateDesc;

  RenderContext(CreateDesc& desc);

  virtual ~RenderContext() = default;

  void beginRender();

  void endRender();

  void commit(RenderCommandBuffer& cmdBuff);

  void setFrameBufferSize(Vec2f newSize);

protected:
  virtual void onBeginRender() = 0;

  virtual void onEndRender() = 0;

  virtual void onCommit(RenderCommandBuffer& cmdBuff) = 0;

  virtual void onSetFrameBufferSize(Vec2f newSize) = 0;

  template<class T> // Issue: typename T, class IMPL
  void _dispatch(T* impl, RenderCommandBuffer& cmdBuff);

  Vec2f _frameBufferSize{0.0f, 0.0f}; /**< Issue: Vec2f, x, y, Operator+-  */
};

/**
 * @brief protected member template function
 *
 * Utilize the type of Render Command Buffer to execute the DrawCall
 *
 * @tparam T
 * @param impl
 * @param cmdBuff
 */
template<class T>
void RenderContext::_dispatch(T* impl, RenderCommandBuffer& cmdBuff) {
  using CmdType = RenderCommandType;

#define CMD_CASE(CMD_NAME)                                   \
  case CmdType::CMD_NAME: {                                  \
    auto* pCmd = static_cast<RenderCommand##CMD_NAME*>(cmd); \
    impl->onCmd_##CMD_NAME(*pCmd);                           \
  } break;

  for (auto* cmd : cmdBuff.commands()) {
    switch (cmd->getType()) {
      CMD_CASE(ClearFrameBuffer)
      CMD_CASE(SwapBuffer)
      CMD_CASE(DrawCall)
      default: throw LIBNG_ERROR("Error: Undefined Render Command"); break;
    }
  }
#undef CMD_CASE
}

} // namespace libng