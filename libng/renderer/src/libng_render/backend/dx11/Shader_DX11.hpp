#pragma once

#include <libng_render/RendererCommon.hpp>

#include <libng_render/material/Shader.hpp>
#include <libng_render/material/ShaderInfo.hpp>
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
    void load(ShaderPass_DX11* pass, //
              StrView passPath,      //
              DX11_ID3DDevice* dev); //

    void bind(RenderContext_DX11* ctx);

    ByteSpan bytecode() const;

  private:
    ComPtr<DX11_ID3DVertexShader> _shader;
    Vector<u8> _bytecode;
  };

  struct PixelStage_DX11 : public ShaderPixelStage {
    void load(ShaderPass_DX11* pass, //
              StrView passPath,      //
              DX11_ID3DDevice* dev); //

    void bind(RenderContext_DX11* ctx);

    ByteSpan bytecode() const;

  private:
    ComPtr<DX11_ID3DPixelShader> _shader;
    Vector<u8> _bytecode;
  };

  struct ShaderPass_DX11 : public ShaderPass {
    using Base = ShaderPass;

    ShaderPass_DX11(Shader_DX11* shader,     //
                    StrView passPath,        //
                    ShaderInfo::Pass& info); //
    ~ShaderPass_DX11();

  private:
    VertexStage_DX11 _vertexStage_DX11;
    PixelStage_DX11 _pixelStage_DX11;
  };
};

} // namespace libng