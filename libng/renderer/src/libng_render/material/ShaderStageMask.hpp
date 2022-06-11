#pragma once

namespace libng {

enum class ShaderStageMask
{
  None,
  Vertex = 1 << 0,
  Pixel  = 1 << 1,
};

} // namespace libng