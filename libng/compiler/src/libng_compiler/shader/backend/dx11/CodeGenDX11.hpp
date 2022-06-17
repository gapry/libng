#pragma once

#include <libng_core/libcxx/string_view.hpp>
#include <libng_core/libcxx/span.hpp>
#include <libng_core/file/MemMapFile.hpp>
#include <libng_core/platform/graphics.hpp>
#include <libng_render/material/ShaderStageMask.hpp>
#include <libng_render/material/ShaderStageInfo.hpp>
#include <libng_render/type/RenderDataType.hpp>
#include <libng_render/backend/dx11/DX11Util.hpp>
#include <libng_render/backend/dx11/TypeDX11.hpp>

namespace libng {

class CodeGenDX11 {
  using Util     = DX11Util;
  using DataType = RenderDataType;

public:
  CodeGenDX11();

private:
  void _inputs();
  void _constBuffers();
  void _textures();
  void _samplers();
};

} // namespace libng