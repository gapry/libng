#include <libng_render/backend/dx11/Shader_DX11.hpp>

namespace libng {

Shader_DX11::Shader_DX11(StrView filename)
  : Base(filename) {
  LIBNG_LOG("{}\n", __LIBNG_PRETTY_FUNCTION__);
}

Shader_DX11::~Shader_DX11() {
  LIBNG_LOG("{}\n", __LIBNG_PRETTY_FUNCTION__);
}

void Shader_DX11::loadStageFile(StrView passPath,           //
                                ShaderStageMask stageMask,  //
                                Vector<u8>& outBytecode,    //
                                ShaderStageInfo& outInfo) { //
  auto* profile = Util::getDxStageProfile(stageMask);

  auto filename = Fmt("{}/{}.bin", passPath, profile);
  File::readFile(filename, outBytecode);

  filename += ".json";
  JsonUtil::readFile(filename, outInfo);
}

void Shader_DX11::VertexStage_DX11::load(ShaderPass_DX11* pass, //
                                         StrView passPath,      //
                                         DX11_ID3DDevice* dev) {
  loadStageFile(passPath,    //
                stageMask(), //
                _bytecode,   //
                _info);      //

  auto hr = dev->CreateVertexShader(_bytecode.data(),      //
                                    _bytecode.size(),      //
                                    nullptr,               //
                                    _shader.ptrForInit()); //
  Util::throwIfError(hr);
}

void Shader_DX11::VertexStage_DX11::bind(RenderContext_DX11* ctx) {
  auto* dc = ctx->renderer()->d3dDeviceContext();
  if (!_shader) {
    throw LIBNG_ERROR("{}\n", "dx shader is null");
  }
  dc->VSSetShader(_shader, 0, 0);
}

ByteSpan Shader_DX11::VertexStage_DX11::bytecode() const {
  return _bytecode;
}

void Shader_DX11::PixelStage_DX11::load(ShaderPass_DX11* pass, //
                                        StrView passPath,      //
                                        DX11_ID3DDevice* dev) {
  loadStageFile(passPath,    //
                stageMask(), //
                _bytecode,   //
                _info);      //

  auto hr = dev->CreatePixelShader(_bytecode.data(),      //
                                   _bytecode.size(),      //
                                   nullptr,               //
                                   _shader.ptrForInit()); //
  Util::throwIfError(hr);
}

void Shader_DX11::PixelStage_DX11::bind(RenderContext_DX11* ctx) {
  auto* dc = ctx->renderer()->d3dDeviceContext();
  if (!_shader) {
    throw LIBNG_ERROR("{}\n", "dx shader is null");
  }
  dc->PSSetShader(_shader, 0, 0);
}

ByteSpan Shader_DX11::PixelStage_DX11::bytecode() const {
  return _bytecode;
}

} // namespace libng
