#include <libng_compiler/shader/backend/dx11/CodeGenDX11.hpp>

namespace libng {

#if defined(LIBNG_OS_WINDOWS) && defined(LIBNG_RENDER_DX11)

void CodeGenDX11::Execute(StrView outPath,             //
                          ShaderStageMask shaderStage, //
                          StrView srcFilename,         //
                          StrView entryFunc) {         //
  LIBNG_LOG("CodeGen Stage = {}\n", __LIBNG_FUNCTION__);

  TempStringA entryPoint = entryFunc;
  LIBNG_LOG("entry point = {}\n", entryPoint);

  MemMapFile mmapFile;
  mmapFile.open(srcFilename);
  LIBNG_LOG("memMapFileName = {}\n", mmapFile.filename().c_str());

  auto profile = Util::getDxStageProfile(shaderStage);
  LIBNG_LOG("profile = {}\n", profile);

  // https://docs.microsoft.com/en-us/windows/win32/direct3dhlsl/d3dcompile-constants
  UINT flags1 = 0; // D3DCOMPILE_PACK_MATRIX_ROW_MAJOR;
  UINT flags2 = 0;
#if _DEBUG
  // flags1 |= D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
#endif

  ComPtr<ID3DBlob> byteCode;
  ComPtr<ID3DBlob> errorMsg;

  auto hlsl = mmapFile.span();

  // https://docs.microsoft.com/en-us/windows/win32/api/d3dcompiler/nf-d3dcompiler-d3dcompile
  auto hr = D3DCompile2(hlsl.data(),                 //
                        hlsl.size(),                 //
                        mmapFile.filename().c_str(), //
                        nullptr,                     //
                        nullptr,                     //
                        entryPoint.c_str(),          //
                        profile,                     //
                        flags1,                      //
                        flags2,                      //
                        0,                           //
                        nullptr,                     //
                        0,                           //
                        byteCode.ptrForInit(),       //
                        errorMsg.ptrForInit());      //

  if (FAILED(hr)) {
    throw LIBNG_ERROR("HRESULT = {}\n Error Message: {}", hr, Util::toStrView(errorMsg));
  }

  Directory::create(outPath);
  auto byteCodeSpan = Util::toSpan(byteCode);
  auto outFileName  = Fmt("{}/{}.bin", outPath, profile);
  File::writeFileIfChanged(outFileName, byteCodeSpan, true, true);
  LIBNG_LOG("outputFileName = {}\n", outFileName);
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