#pragma once

#include <libng_render/RendererCommon.hpp>

#include <libng_render/AdapterInfo.hpp>
#include <libng_render/material/Material.hpp>
#include <libng_render/material/Shader.hpp>
#include <libng_render/textures/Texture2D.hpp>
#include <libng_render/textures/Texture2D_CreateDesc.hpp>

// clang-format off

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
    ~CreateDesc();

    ApiType apiType;
    bool multithread : 1;
  };

  static Renderer* instance();
  static Renderer* create(CreateDesc& desc);

           Renderer();
  virtual ~Renderer();

  SPtr<RenderContext> createContext  (RenderContextCreateDesc& desc);
  SPtr<GPUBuffer>     createGPUBuffer(GPUBufferCreateDesc& desc);
  SPtr<Texture2D>     createTexture2D(Texture2D_CreateDesc& desc);
  SPtr<Shader>        createShader   (StrView filename);
  SPtr<Material>      createMaterial ();

  void onShaderDestory(Shader* shader);

  struct StockTextures {
    SPtr<Texture2D> white;
    SPtr<Texture2D> black;
    SPtr<Texture2D> red;
    SPtr<Texture2D> green;
    SPtr<Texture2D> blue;
    SPtr<Texture2D> magenta;
    SPtr<Texture2D> error;
  };

  StockTextures stockTextures;

  SPtr<Texture2D> createSolidColorTexture2D(const math::Color4b& color);

  const AdapterInfo& adapterInfo() const;
                bool       vsync() const;

protected:
  static Renderer* s_instance;

  virtual SPtr<RenderContext> onCreateContext  (RenderContextCreateDesc& desc) = 0;
  virtual SPtr<GPUBuffer>     onCreateGPUBuffer(GPUBufferCreateDesc& desc)     = 0;
  virtual SPtr<Texture2D>     onCreateTexture2D(Texture2D_CreateDesc& desc)    = 0;
  virtual SPtr<Shader>        onCreateShader   (StrView filename)              = 0;
  virtual SPtr<Material>      onCreateMaterial ()                              = 0;

  StringMap<Shader*> _shaders;
  AdapterInfo        _adapterInfo;
         bool        _vsync : 1;
};

} // namespace libng