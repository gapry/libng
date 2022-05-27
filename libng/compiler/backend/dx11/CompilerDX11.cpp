#include <compiler/backend/dx11/CompilerDX11.hpp>
#include <memory/ComPtr.hpp>

namespace libng {

CompilerDX11::CompilerDX11(CreateDesc& desc) {
  TempStringA entryPoint = desc.entryFunc;

  MemMapFile memmap;
  memmap.open(desc.srcFilename);

  UINT flags1 = 0; // D3DCOMPILE_PACK_MATRIX_ROW_MAJOR;
  UINT flags2 = 0;

  auto hlsl = memmap.span();

  auto profile = ShaderCompilerUtil::getDxStageProfile(desc.shaderStage);

  ComPtr<ID3DBlob> byteCode;
  ComPtr<ID3DBlob> errorMsg;

  auto hr = D3DCompile2(hlsl.data(),               //
                        hlsl.size(),               //
                        memmap.filename().c_str(), //
                        nullptr,                   //
                        nullptr,                   //
                        entryPoint.c_str(),        //
                        profile,                   //
                        flags1,                    //
                        flags2,                    //
                        0,                         //
                        nullptr,                   //
                        0,                         //
                        byteCode.ptrForInit(),     //
                        errorMsg.ptrForInit());    //
}

} // namespace libng