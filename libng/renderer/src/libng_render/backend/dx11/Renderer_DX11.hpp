#pragma once

#include <libng_render/Renderer.hpp>
#include <libng_render/backend/dx11/GPUBuffer_DX11.hpp>
#include <libng_render/backend/dx11/Material_DX11.hpp>
#include <libng_render/backend/dx11/Renderer_DX11.hpp>
#include <libng_render/backend/dx11/Shader_DX11.hpp>
#include <libng_render/backend/dx11/Texture2D_DX11.hpp>
#include <libng_render/backend/dx11/Util_DX11.hpp>

namespace libng {

class Renderer_DX11 : public Renderer {
  using Base = Renderer;
  using Util = Util_DX11;

public:
  static Renderer_DX11* instance() {
    return static_cast<Renderer_DX11*>(s_instance);
  }

  Renderer_DX11(CreateDesc& desc);

  DX11_IDXGIFactory* dxgiFactory() {
    return _dxgiFactory;
  }

  DX11_IDXGIDevice* dxgiDevice() {
    return _dxgiDevice;
  }

  DX11_IDXGIAdapter* dxgiAdapter() {
    return _dxgiAdapter;
  }

  DX11_ID3DDevice* d3dDevice() {
    return _d3dDevice;
  }

  DX11_ID3DDeviceContext* d3dDeviceContext() {
    return _d3dDeviceContext;
  }

  DX11_ID3DDebug* d3dDebug() {
    return _d3dDebug;
  }

protected:
  // clang-format off
  virtual SPtr<RenderContext> onCreateContext  (RenderContextCreateDesc& desc) override;
  virtual SPtr<GPUBuffer>     onCreateGPUBuffer(GPUBufferCreateDesc& desc)     override;
  virtual SPtr<Texture2D>     onCreateTexture2D(Texture2D_CreateDesc& desc)    override;
  virtual SPtr<Material>      onCreateMaterial (void)                          override;
  virtual SPtr<Shader>        onCreateShader   (StrView filename)              override;

  ComPtr<DX11_IDXGIFactory>      _dxgiFactory;
  ComPtr<DX11_IDXGIDevice>       _dxgiDevice;
  ComPtr<DX11_IDXGIAdapter>      _dxgiAdapter;

  ComPtr<DX11_ID3DDevice>        _d3dDevice;
  ComPtr<DX11_ID3DDeviceContext> _d3dDeviceContext;
  ComPtr<DX11_ID3DDebug>         _d3dDebug;
};

} // namespace libng