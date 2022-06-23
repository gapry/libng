#include <libng_compiler/shader/backend/dx11/CodeGenDX11.hpp>

namespace libng {

#if defined(LIBNG_OS_WINDOWS) && defined(LIBNG_RENDER_DX11)

void CodeGenDX11::Execute(StrView outFilename,         //
                          ShaderStageMask shaderStage, //
                          StrView srcFilename,         //
                          StrView entryFunc) {         //
  LIBNG_LOG("CodeGen Stage = {}\n", __LIBNG_FUNCTION__);

  TempStringA entryPoint = entryFunc;
  LIBNG_LOG("entry point = {}\n", entryPoint);

  MemMapFile mapFile;
  mapFile.open(srcFilename);
  LIBNG_LOG("memMapFileName = {}\n", mapFile.filename().c_str());

  auto profile = Util::getDxStageProfile(shaderStage);
  LIBNG_LOG("profile = {}\n", profile);
}

void CodeGenDX11::_Reflect(StrView outFilename,   //
                           ByteSpan bytecode,     //
                           ShaderStageMask stage, //
                           StrView profile) {     //
  LIBNG_LOG("CodeGen Stage = {}\n", __LIBNG_FUNCTION__);
}

void CodeGenDX11::_ReflectInputs(ShaderStageInfo& outInfo,        //
                                 ID3D11ShaderReflection* reflect, //
                                 D3D11_SHADER_DESC& dec) {        //
  LIBNG_LOG("CodeGen Stage = {}\n", __LIBNG_FUNCTION__);
}

void CodeGenDX11::_ReflectConstBuffers(ShaderStageInfo& outInfo,        //
                                       ID3D11ShaderReflection* reflect, //
                                       D3D11_SHADER_DESC& dec) {        //
  LIBNG_LOG("CodeGen Stage = {}\n", __LIBNG_FUNCTION__);
}

void CodeGenDX11::_ReflectTextures(ShaderStageInfo& outInfo,        //
                                   ID3D11ShaderReflection* reflect, //
                                   D3D11_SHADER_DESC& dec) {        //
  LIBNG_LOG("{}\n", __LIBNG_PRETTY_FUNCTION__);
}

void CodeGenDX11::_ReflectSamplers(ShaderStageInfo& outInfo,        //
                                   ID3D11ShaderReflection* reflect, //
                                   D3D11_SHADER_DESC& dec) {        //
  LIBNG_LOG("{}\n", __LIBNG_PRETTY_FUNCTION__);
}
#endif

} // namespace libng