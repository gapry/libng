#include <libng_render/Renderer.hpp>
#include <libng_render/backend/dx11/Renderer_DX11.hpp>

namespace libng {

Renderer* Renderer::s_instance = nullptr;

Renderer::CreateDesc::CreateDesc()
  : multithread(false) {
#if LIBNG_OS_WINDOWS
  apiType = ApiType::DX11;
#else
  apiType = ApiType::None;
#endif
}

Renderer::CreateDesc::~CreateDesc() {
}

Renderer* Renderer::instance() {
  return s_instance;
}

Renderer* Renderer::create(CreateDesc& desc) {
  Renderer* instance = nullptr;
  switch (desc.apiType) {
    case ApiType::DX11: instance = new Renderer_DX11(desc); break;
    case ApiType::OpenGL: break;
    default: throw LIBNG_ERROR("{}\n", "Doesn't find the supported Graphic API"); break;
  }
  return instance;
}

Renderer::Renderer() {
  LIBNG_ASSERT(s_instance == nullptr);
  s_instance = this;
  _vsync     = true;
}

Renderer::~Renderer() {
  LIBNG_ASSERT(s_instance == this);
  s_instance = nullptr;
}

SPtr<RenderContext> Renderer::createContext(RenderContextCreateDesc& desc) {
  return onCreateContext(desc);
}

SPtr<GPUBuffer> Renderer::createGPUBuffer(GPUBufferCreateDesc& desc) {
  return onCreateGPUBuffer(desc);
}

SPtr<Texture2D> Renderer::createTexture2D(Texture2D_CreateDesc& desc) {
  return onCreateTexture2D(desc);
}

SPtr<Shader> Renderer::createShader(StrView filename) {
  TempString tmpName = filename;

  auto it = _shaders.find(tmpName.c_str());
  if (it != _shaders.end()) {
    return it->second;
  }

  auto shader               = onCreateShader(tmpName);
  _shaders[tmpName.c_str()] = shader.ptr();
  return shader;
}

SPtr<Material> Renderer::createMaterial() {
  return onCreateMaterial();
}

void Renderer::onShaderDestory(Shader* shader) {
  _shaders.erase(shader->filename().c_str());
}

const AdapterInfo& Renderer::adapterInfo() const {
  return _adapterInfo;
}

bool Renderer::vsync() const {
  return _vsync;
}

} // namespace libng