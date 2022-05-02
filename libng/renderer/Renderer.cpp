#include <renderer/Renderer.hpp>
#include <exception/error.hpp>
#include <platform/os.hpp>

namespace libng {

Renderer* Renderer::_s_current = nullptr; // Issue: redundant assignment: ctor & global

/**
 * @brief The public inner class constructor
 * 
 * 1. select the graphic api in runtime
 * 2. determine the renderer support the multi-thread or not in compile-time
 * 
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

Renderer* Renderer::current() {
  return _s_current;
}

/**
 * @brief public static member function
 * 
 * create the instance of the renderer which the graphic API is selected in ctor
 *
 * @param desc 
 * @return Renderer* 
 */
Renderer* Renderer::create(CreateDesc& desc) {
  Renderer* p = nullptr;
  switch (desc.apiType) {
    case APIType::DX11: break;
    case APIType::OpenGL: break;
    default: throw LIBNG_ERROR("[ERROR] doesn't find the supported Graphic API"); break;
  }
}

/**
 * @brief Construct a new Renderer:: Renderer object
 * 
 * use the protected static raw pointer to hold the instance object in runtime
 * enable vsync or not
 * 
 */
Renderer::Renderer() {
  LIBNG_ASSERT(_s_current == nullptr);
  _s_current = this;
  _vsync     = true;
}

Renderer::~Renderer() {
  LIBNG_ASSERT(_s_current == this);
  _s_current = nullptr;
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
 * call the pure virtual protected function `onCreateContext(RenderContextCreateDesc&)`
 *
 * @param desc
 * @return RenderContext*
 */
RenderContext* Renderer::createContext(RenderContextCreateDesc& desc) {
  return onCreateContext(desc);
}

/**
 * @brief public member function
 *
 * call the pure virtual protected function `onCreateGPUBuffer(GPUBufferCreateDesc&)`
 *
 * @param desc
 * @return GPUBuffer*
 */
GPUBuffer* Renderer::createGPUBuffer(GPUBufferCreateDesc& desc) {
  return onCreateGPUBuffer(desc);
}

} // namespace libng