#include <libng_core/exception/error.hpp>
#include <libng_core/platform/os.hpp>
#include <libng_render/Renderer.hpp>
#include <libng_render/backend/dx11/RendererDX11.hpp>

namespace libng {

Renderer* Renderer::_current = nullptr; // Issue: redundant assignment: ctor & global

/**
 * @brief Public inner class constructor
 *
 * 1. select the graphic api in runtime.
 * 2. determine the renderer support the multi-thread or not in compile-time.
 */
Renderer::CreateDesc::CreateDesc()
  : multithread(false) {
#if LIBNG_OS_WINDOWS
  apiType = APIType::DX11;
#else
  apiType = APIType::None;
#endif
}

Renderer::CreateDesc::~CreateDesc() {
}

/**
 * @brief public static member function
 *
 * @return Renderer*
 */
Renderer* Renderer::current() {
  return _current;
}

/**
 * @brief public static member function
 *
 * create the instance of the renderer which the graphic API is selected in ctor.
 *
 * @param desc
 * @return Renderer*
 */
Renderer* Renderer::create(CreateDesc& desc) {
  Renderer* p = nullptr;
  switch (desc.apiType) {
    case APIType::DX11: p = new RendererDX11(desc); break;
    case APIType::OpenGL: break;
    default: throw LIBNG_ERROR("[ERROR] doesn't find the supported Graphic API"); break;
  }
  return p;
}

/**
 * @brief Construct a new Renderer object
 *
 * 1. use the protected static raw pointer to hold the instance object in runtime.
 * 2. enable vsync or not.
 * 3. since it's critical, it prohibit to utilize the execption/if as `_current` is `nullptr`
 */
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

/**
 * @brief public member function
 *
 * call the pure virtual protected function `onCreateContext(RenderContextCreateDesc&)`.
 *
 * @param desc
 * @return RenderContext*
 */
SPtr<RenderContext> Renderer::createContext(RenderContextCreateDesc& desc) {
  return onCreateContext(desc);
}

/**
 * @brief public member function
 *
 * call the pure virtual protected function `onCreateGPUBuffer(GPUBufferCreateDesc&)`.
 *
 * @param desc
 * @return GPUBuffer*
 */
SPtr<GPUBuffer> Renderer::createGPUBuffer(GPUBufferCreateDesc& desc) {
  return onCreateGPUBuffer(desc);
}

SPtr<Shader> Renderer::createShader(StrView filename) {
  return onCreateShader(filename);
}

SPtr<Material> Renderer::createMaterial() {
  return onCreateMaterial();
}

} // namespace libng