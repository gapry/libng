#pragma once

#include <libng_render/Renderer.hpp>
#include <libng_render/backend/dx11/DX11Util.hpp>
#include <libng_render/backend/dx11/GPUBufferDX11.hpp>
#include <libng_render/backend/dx11/Material_DX11.hpp>
#include <libng_render/backend/dx11/RendererDX11.hpp>
#include <libng_render/backend/dx11/Shader_DX11.hpp>
#include <libng_render/backend/dx11/Texture2D_DX11.hpp>

namespace libng {

class RendererDX11 : public Renderer {
  using Base = Renderer;
  using Util = DX11Util;

public:
  static RendererDX11* current() {
    return static_cast<RendererDX11*>(s_instance);
  }

  RendererDX11(CreateDesc& desc);

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