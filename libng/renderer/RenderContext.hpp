#pragma once

#include <types/Object.hpp>

#include <math/Vector/Vec2.hpp>

#include <renderer/RenderContextCreateDesc.hpp>
#include <renderer/command/RenderCommandType.hpp>
#include <renderer/buffer/RenderCommandBuffer.hpp>

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
  void _dispatch(T* impl, const RenderCommandBuffer& cmdBuff);

  Vec2f _frameBuffSize{0.0f, 0.0f}; /**< Issue: Vec2f, x, y, Operator+-  */
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
void RenderContext::_dispatch(T* const impl, const RenderCommandBuffer& cmdBuff) {
  using CmdType = RenderCommandType;

#define CMD_CASE(CMD_NAME)                                   \
  case CmdType::CMD_NAME: {                                  \
    auto* pCmd = static_cast<RenderCommand##CMD_NAME*>(cmd); \
    impl->onCmd##CMD_NAME(*pCmd);                            \
  } break;

  for (auto* cmd : cmdBuff.commands()) {
    switch (cmd->type()) {
      CMD_CASE(ClearFrameBuffers)
      CMD_CASE(SwapBuffers)
      CMD_CASE(DrawCall)
      default: throw LIBNG_ERROR("Error: Undefined Render Command"); break;
    }
  }
#undef CMD_CASE
}

} // namespace libng