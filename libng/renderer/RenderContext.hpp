#pragma once

#include <types/Object.hpp>
#include <renderer/command/RenderCommandBuffer.hpp>

namespace libng {

class RenderContext : public Object {
public:
  RenderContext();

protected:
  template<class T> // Issue: typename T, class IMPL
  void _dispatch(T* impl, RenderCommandBuffer& cmdBuff);
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