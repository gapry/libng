#pragma once

namespace libng {

enum class RenderCommandType
{
  None,
  ClearFrameBuffers,
  SwapBuffers,
  DrawCall,
};

} // namespace libng