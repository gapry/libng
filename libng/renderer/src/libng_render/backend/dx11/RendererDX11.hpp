#pragma once

#include <libng_core/memory/ComPtr.hpp>
#include <libng_render/Renderer.hpp>
#include <libng_render/backend/dx11/DX11Util.hpp>
#include <libng_render/backend/dx11/GPUBufferDX11.hpp>
#include <libng_render/backend/dx11/RendererDX11.hpp>

namespace libng {

class RendererDX11 : public Renderer {
  using Base = Renderer;
  using Util = DX11Util;

public:
  static RendererDX11* current() {
    return static_cast<RendererDX11*>(_current);
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
  virtual RenderContext* onCreateContext(RenderContextCreateDesc& desc) override;

  virtual GPUBuffer* onCreateGPUBuffer(GPUBufferCreateDesc& desc) override;

  ComPtr<DX11_IDXGIFactory> _dxgiFactory;
  ComPtr<DX11_IDXGIDevice> _dxgiDevice;
  ComPtr<DX11_IDXGIAdapter> _dxgiAdapter;
  ComPtr<DX11_ID3DDevice> _d3dDevice;
  ComPtr<DX11_ID3DDeviceContext> _d3dDeviceContext;
  ComPtr<DX11_ID3DDebug> _d3dDebug;
};

} // namespace libng