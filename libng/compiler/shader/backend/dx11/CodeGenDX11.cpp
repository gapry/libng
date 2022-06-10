#include <compiler/shader/backend/dx11/CodeGenDX11.hpp>

#include <memory/ComPtr.hpp>

namespace libng {

CodeGenDX11::CodeGenDX11(CreateDesc& desc) {
  TempStringA entryPoint = desc.entryFunc;

  MemMapFile memmap;
  memmap.open(desc.srcFilename);

  UINT flags1 = 0; // D3DCOMPILE_PACK_MATRIX_ROW_MAJOR;
  UINT flags2 = 0;

  auto hlsl = memmap.span();

  auto profile = ShaderUtil::getStageProfile(desc.shaderStage);

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
  if (FAILED(hr)) {
    LIBNG_ERROR("{}\n", "Shader Code Gen");
  }
}

void CodeGenDX11::Reflect::execute() {
  _inputs();
  _constBuffers();
  _textures();
  _samplers();
}

void CodeGenDX11::Reflect::_inputs() {
}

void CodeGenDX11::Reflect::_constBuffers() {
}

void CodeGenDX11::Reflect::_textures() {
}

void CodeGenDX11::Reflect::_samplers() {
}

} // namespace libng