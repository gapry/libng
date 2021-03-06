#pragma once

#include <libng_render/RendererCommon.hpp>

#include <libng_render/material/ShaderStageInfo.hpp>
#include <libng_render/material/ShaderStageMask.hpp>
#include <libng_render/type/RenderDataType.hpp>
#include <libng_render/vertex/VertexSemanticType.hpp>

#include <libng_render/backend/dx11/Type_DX11.hpp>
#include <libng_render/backend/dx11/Util_DX11.hpp>

namespace libng {

#if defined(LIBNG_OS_WINDOWS) && defined(LIBNG_RENDER_DX11)

class CodeGenDX11 {
  using Util     = Util_DX11;
  using DataType = RenderDataType;

public:
  void Execute(StrView outPath,             //
               ShaderStageMask shaderStage, //
               StrView srcFilename,         //
               StrView entryFunc);          //

private:
  void _Reflect(StrView outFilename,   //
                ByteSpan bytecode,     //
                ShaderStageMask stage, //
                StrView profile);      //

  // https://docs.microsoft.com/en-us/windows/win32/api/d3d11shader/nn-d3d11shader-id3d11shaderreflection
  // https://docs.microsoft.com/en-us/windows/win32/api/d3d11shader/ns-d3d11shader-d3d11_shader_desc
  void _ReflectInputs(ShaderStageInfo& outInfo,        //
                      ID3D11ShaderReflection* reflect, //
                      D3D11_SHADER_DESC& dec);         //

  void _ReflectConstBuffers(ShaderStageInfo& outInfo,        //
                            ID3D11ShaderReflection* reflect, //
                            D3D11_SHADER_DESC& dec);         //

  void _ReflectTextures(ShaderStageInfo& outInfo,        //
                        ID3D11ShaderReflection* reflect, //
                        D3D11_SHADER_DESC& dec);         //

  void _ReflectSamplers(ShaderStageInfo& outInfo,        //
                        ID3D11ShaderReflection* reflect, //
                        D3D11_SHADER_DESC& dec);         //
};
#endif

} // namespace libng