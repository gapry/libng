#pragma once

#include <libng_render/RendererCommon.hpp>

#include <libng_render/RenderContext.hpp>
#include <libng_render/command/RenderCommandClearFrameBuffer.hpp>
#include <libng_render/command/RenderCommandDrawCall.hpp>
#include <libng_render/command/RenderCommandSwapBuffer.hpp>

#include <libng_render/backend/dx11/RendererDX11.hpp>
#include <libng_render/backend/dx11/DX11Util.hpp>
#include <libng_render/backend/dx11/GPUBufferDX11.hpp>
#include <libng_render/backend/dx11/TypeDX11.hpp>

namespace libng {

// clang-format off

class RenderContextDX11 : public RenderContext {
  using Base = RenderContext;

public:
  using Util = DX11Util;
  
  RenderContextDX11(CreateDesc& desc);

  void onCmd_ClearFrameBuffer(RenderCommandClearFrameBuffer& cmd);
  void onCmd_SwapBuffer      (RenderCommandSwapBuffer& cmd);
  void onCmd_DrawCall        (RenderCommandDrawCall& cmd);

protected:
  RendererDX11* _renderer = nullptr;

  ComPtr<DX11_IDXGISwapChain>        _swapChain;
  ComPtr<DX11_ID3DRenderTargetView>  _renderTargetView;
  ComPtr<DX11_ID3DTexture2D>         _depthStencil;
  ComPtr<DX11_ID3DDepthStencilView>  _depthStencilView;

  ComPtr<DX11_ID3DBuffer>            _testVertexBuffer;
  ComPtr<DX11_ID3DVertexShader>      _testVertexShader;
  ComPtr<DX11_ID3DBlob>              _testVertexShaderBytecode;
  ComPtr<DX11_ID3DPixelShader>       _testPixelShader;
  ComPtr<DX11_ID3DRasterizerState>   _testRasterizerState;

  ComPtr<DX11_ID3DDepthStencilState> _testDepthStencilState;
  ComPtr<DX11_ID3DBlendState>        _testBlendState;

  VectorMap<const VertexLayout*, ComPtr<DX11_ID3DInputLayout>> _testInputLayouts;
  
  DX11_ID3DInputLayout* _getTestInputLayout(const VertexLayout* src);

  void _createRenderTarget();
  void _setTestShaders    ();

  virtual void onBeginRender() override;
  virtual void onEndRender  () override;

  virtual void onSetFrameBufferSize(math::Vec2f newSize);
  virtual void onCommit            (RenderCommandBuffer& cmdBuf);
};

} // namespace libng