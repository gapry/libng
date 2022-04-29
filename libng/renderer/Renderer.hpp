#pragma once

#include <types/noncopyable.hpp>
#include <renderer/AdapterInfo.hpp>

namespace libng {

class RenderContext;
struct RenderContextCreateDesc;

class GPUBuffer;
struct GPUBufferCreateDesc;

class Renderer : public NonCopyable {
public:
  enum class ApiType
  {
    None,
    DX11,
    OpenGL,
  };

  struct CreateDesc {
    CreateDesc();

    ApiType apiType;
    bool multithread : 1;
  };

  static Renderer* current();

  static Renderer* create(CreateDesc& desc);

  Renderer();

  virtual ~Renderer();

  const AdapterInfo& adapterInfo() const;

  bool vsync() const;

  RenderContext* createContext(RenderContextCreateDesc& desc);

  GPUBuffer* createGpuBuffer(GPUBufferCreateDesc& desc);

protected:
  virtual RenderContext* onCreateContext(RenderContextCreateDesc& desc) = 0;

  virtual GPUBuffer* onCreateGPUBuffer(GPUBufferCreateDesc& desc) = 0;

  static Renderer* _current;

  AdapterInfo _adapterInfo;
  bool _vsync : 1;
};

} // namespace libng