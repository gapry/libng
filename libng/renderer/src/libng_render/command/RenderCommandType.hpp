#pragma once

namespace libng {

enum class RenderCommandType
{
  None,
  ClearFrameBuffer,
  SwapBuffer,
  DrawCall,
};

} // namespace libng