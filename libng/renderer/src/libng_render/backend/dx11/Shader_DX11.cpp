#include <libng_render/backend/dx11/Shader_DX11.hpp>

namespace libng {

Shader_DX11::Shader_DX11(StrView filename)
  : Base(filename) {
  LIBNG_LOG("{}\n", __LIBNG_PRETTY_FUNCTION__);

  auto* proj = ProjectSettings::instance();
  TempString passPath;

  size_t passes_size = _info.passes.size();
  _passes.reserve(passes_size);

  for (size_t i = 0; i < passes_size; i++) {
    FmtTo(passPath, "{}/{}/dx11/pass{}", proj->importedPath(), filename, i);
    auto* pass = new ShaderPass_DX11(this, passPath, _info.passes[i]);
    _passes.emplace_back(pass);
  }
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

Shader_DX11::ShaderPass_DX11::ShaderPass_DX11(Shader_DX11* shader,    //
                                              StrView passPath,       //
                                              ShaderInfo::Pass& info) //
  : Base(shader, info) {
  _vertexStage = &_vertexStage_DX11;
  _pixelStage  = &_pixelStage_DX11;

  auto* renderer = Renderer_DX11::instance();
  auto* dev      = renderer->d3dDevice();

  if (info.vsFunc.size()) {
    _vertexStage_DX11.load(this, passPath, dev);
  }

  if (info.psFunc.size()) {
    _pixelStage_DX11.load(this, passPath, dev);
  }
}

Shader_DX11::ShaderPass_DX11::~ShaderPass_DX11() {
}

} // namespace libng
