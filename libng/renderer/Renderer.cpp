#include <renderer/Renderer.hpp>
#include <exception/error.hpp>
#include <platform/os.hpp>

namespace libng {

Renderer* Renderer::_current = nullptr;

Renderer::CreateDesc::CreateDesc()
  : multithread(false) {
#if LIBNG_OS_WINDOWS
  apiType = ApiType::DX11;
#else
  apiType = ApiType::None;
#endif
}

Renderer* Renderer::current() {
  return _current;
}

Renderer* Renderer::create(CreateDesc& desc) {
  Renderer* p = nullptr;
  switch (desc.apiType) {
    case ApiType::DX11: break;
    case ApiType::OpenGL: break;
    default: throw LIBNG_ERROR("[ERROR] doesn't find the supported Graphic API");
  }
}

Renderer::Renderer() {
  LIBNG_ASSERT(_current == nullptr);
  _current = this;
  _vsync   = true;
}

Renderer::~Renderer() {
  LIBNG_ASSERT(_current == this);
  _current = nullptr;
}

const AdapterInfo& Renderer::adapterInfo() const {
  return _adapterInfo;
}

bool Renderer::vsync() const {
  return _vsync;
}

RenderContext* Renderer::createContext(RenderContextCreateDesc& desc) {
  return onCreateContext(desc);
}

GPUBuffer* Renderer::createGpuBuffer(GPUBufferCreateDesc& desc) {
  return onCreateGPUBuffer(desc);
}

} // namespace libng