#pragma once

#include <libng_core/types/noncopyable.hpp>

#include <libng_render/AdapterInfo.hpp>
#include <libng_render/material/Material.hpp>
#include <libng_render/material/Shader.hpp>

namespace libng {

class RenderContext;
struct RenderContextCreateDesc;

class GPUBuffer;
struct GPUBufferCreateDesc;

class Renderer : public NonCopyable {
public:
  enum class APIType
  {
    None,
    DX11,
    OpenGL,
  };

  struct CreateDesc {
    CreateDesc();

    ~CreateDesc();

    APIType apiType;

    bool multithread : 1;
  };

  static Renderer* current();

  static Renderer* create(CreateDesc& desc);

  Renderer();

  virtual ~Renderer();

  const AdapterInfo& adapterInfo() const;

  bool vsync() const;

  RenderContext* createContext(RenderContextCreateDesc& desc);

  GPUBuffer* createGPUBuffer(GPUBufferCreateDesc& desc);

protected:
  // clang-format off
  virtual RenderContext* onCreateContext  (RenderContextCreateDesc& desc) = 0;
  virtual GPUBuffer*     onCreateGPUBuffer(GPUBufferCreateDesc& desc)     = 0;
  virtual Shader*        onCreateShader   (StrView filename)              = 0;
  virtual Material*      onCreateMaterial ()                              = 0;
  // clang-format on

  static Renderer* _current;
  AdapterInfo _adapterInfo;
  bool _vsync : 1;
};

} // namespace libng