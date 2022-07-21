#pragma once

#include <libng_render/RendererCommon.hpp>

#include <libng_render/material/Shader.hpp>
#include <libng_render/material/ShaderPass.hpp>
#include <libng_render/material/ShaderPixelStage.hpp>
#include <libng_render/material/ShaderStageInfo.hpp>
#include <libng_render/material/ShaderStageMask.hpp>
#include <libng_render/material/ShaderVertexStage.hpp>

#include <libng_render/backend/dx11/Util_DX11.hpp>

namespace libng {

class RenderContext_DX11;

class Shader_DX11 : public Shader {
  using Base = Shader;

public:
  using Util = Util_DX11;

  struct ShaderPass_DX11;

  static void loadStageFile(StrView passPath,          //
                            ShaderStageMask stageMask, //
                            Vector<u8>& outBytecode,   //
                            ShaderStageInfo& outInfo); //

  Shader_DX11(StrView filename);
  ~Shader_DX11();

  struct VertexStage_DX11 : public ShaderVertexStage {
  private:
  };

  struct PixelStage_DX11 : public ShaderPixelStage {
  private:
  };

  struct ShaderPass_DX11 : public ShaderPass {
  private:
  };
};

} // namespace libng