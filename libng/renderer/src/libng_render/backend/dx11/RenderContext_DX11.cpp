#pragma once

#include <libng_render/backend/dx11/RenderContext_DX11.hpp>

namespace libng {

RenderContext_DX11::RenderContext_DX11(CreateDesc& desc)
  : Base(desc) {
  _renderer = Renderer_DX11::instance();

  auto* win = static_cast<MSWindow*>(desc.window);

  auto* dev         = _renderer->d3dDevice();
  auto* dxgiFactory = _renderer->dxgiFactory();

  {
    DXGI_SWAP_CHAIN_DESC swapChainDesc               = {};
    swapChainDesc.BufferDesc.Width                   = 8;
    swapChainDesc.BufferDesc.Height                  = 8;
    swapChainDesc.BufferDesc.Format                  = DXGI_FORMAT_R8G8B8A8_UNORM;
    swapChainDesc.BufferDesc.RefreshRate.Numerator   = 60;
    swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
    swapChainDesc.SampleDesc.Count                   = 1;
    swapChainDesc.SampleDesc.Quality                 = 0;
    swapChainDesc.BufferCount                        = 1;
    swapChainDesc.BufferUsage                        = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    swapChainDesc.OutputWindow                       = win->_hwnd;
    swapChainDesc.Windowed                           = TRUE;
    swapChainDesc.SwapEffect                         = DXGI_SWAP_EFFECT_DISCARD;
    swapChainDesc.Flags                              = 0;

    auto hr = dxgiFactory->CreateSwapChain(dev, &swapChainDesc, _swapChain.ptrForInit());
    Util::throwIfError(hr);
  }
}

void RenderContext_DX11::onCmd_ClearFrameBuffer(RenderCommandClearFrameBuffer& cmd) {
  auto* ctx = _renderer->d3dDeviceContext();
  if (_renderTargetView && cmd.color.has_value()) {
    ctx->ClearRenderTargetView(_renderTargetView, cmd.color->data);
  }
  if (_depthStencilView && cmd.depth.has_value()) {
    ctx->ClearDepthStencilView(_depthStencilView, D3D11_CLEAR_DEPTH, *cmd.depth, 0);
  }
}

void RenderContext_DX11::onCmd_DrawCall(RenderCommandDrawCall& cmd) {
  if (!cmd.vertexLayout) {
    LIBNG_ASSERT(false);
    return;
  }

  auto* vertexBuffer = static_cast<GPUBuffer_DX11*>(cmd.vertexBuffer.ptr());
  if (!vertexBuffer) {
    LIBNG_ASSERT(false);
    return;
  }

  if (cmd.vertexCount <= 0) {
    LIBNG_ASSERT(false);
    return;
  }
  if (cmd.primitive == RenderPrimitiveType::None) {
    LIBNG_ASSERT(false);
    return;
  }

  GPUBuffer_DX11* indexBuffer = nullptr;
  if (cmd.indexCount > 0) {
    indexBuffer = static_cast<GPUBuffer_DX11*>(cmd.indexBuffer.ptr());
    if (!indexBuffer) {
      LIBNG_ASSERT(false);
      return;
    }
  }

  _setTestShaders();

  auto* ctx      = _renderer->d3dDeviceContext();
  auto primitive = Util::getDxPrimitiveTopology(cmd.primitive);
  ctx->IASetPrimitiveTopology(primitive);

  auto* inputLayout = _getTestInputLayout(cmd.vertexLayout);
  if (!inputLayout) {
    LIBNG_ASSERT(false);
    return;
  }

  ctx->IASetInputLayout(inputLayout);

  UINT stride      = static_cast<UINT>(cmd.vertexLayout->stride);
  UINT offset      = 0;
  UINT vertexCount = static_cast<UINT>(cmd.vertexCount);
  UINT indexCount  = static_cast<UINT>(cmd.indexCount);

  DX11_ID3DBuffer* ppVertexBuffers[] = {vertexBuffer->d3dBuf()};
  ctx->IASetVertexBuffers(0, 1, ppVertexBuffers, &stride, &offset);

  if (indexCount > 0) {
    auto indexType = Util::getDxFormat(cmd.indexType);
    ctx->IASetIndexBuffer(indexBuffer->d3dBuf(), indexType, 0);
    ctx->DrawIndexed(indexCount, 0, 0);
  } else {
    ctx->Draw(vertexCount, 0);
  }
}

void RenderContext_DX11::onCmd_SwapBuffer(RenderCommandSwapBuffer& cmd) {
  auto hr = _swapChain->Present(_renderer->vsync() ? 1 : 0, 0);
  Util::throwIfError(hr);
}

Renderer_DX11* RenderContext_DX11::renderer() {
  return _renderer;
}

void RenderContext_DX11::_createRenderTarget() {
  auto* renderer = Renderer_DX11::instance();
  auto* dev      = renderer->d3dDevice();
  HRESULT hr;

  ComPtr<ID3D11Texture2D> backBuffer;
  hr = _swapChain->GetBuffer(0, IID_PPV_ARGS(backBuffer.ptrForInit()));
  Util::throwIfError(hr);

  hr = dev->CreateRenderTargetView(backBuffer, nullptr, _renderTargetView.ptrForInit());
  Util::throwIfError(hr);

  D3D11_TEXTURE2D_DESC backBufferDesc;
  backBuffer->GetDesc(&backBufferDesc);

  // Create depth stencil texture
  D3D11_TEXTURE2D_DESC descDepth = {};
  descDepth.Width                = backBufferDesc.Width;
  descDepth.Height               = backBufferDesc.Height;
  descDepth.MipLevels            = 1;
  descDepth.ArraySize            = 1;
  descDepth.Format               = DXGI_FORMAT_D24_UNORM_S8_UINT;
  descDepth.SampleDesc.Count     = 1;
  descDepth.SampleDesc.Quality   = 0;
  descDepth.Usage                = D3D11_USAGE_DEFAULT;
  descDepth.BindFlags            = D3D11_BIND_DEPTH_STENCIL;
  descDepth.CPUAccessFlags       = 0;
  descDepth.MiscFlags            = 0;
  hr                             = dev->CreateTexture2D(&descDepth, nullptr, _depthStencil.ptrForInit());
  Util::throwIfError(hr);

  // Create the depth stencil view
  D3D11_DEPTH_STENCIL_VIEW_DESC descDSV = {};
  descDSV.Format                        = descDepth.Format;
  descDSV.ViewDimension                 = D3D11_DSV_DIMENSION_TEXTURE2D;
  descDSV.Texture2D.MipSlice            = 0;
  hr = dev->CreateDepthStencilView(_depthStencil.ptr(), &descDSV, _depthStencilView.ptrForInit());
  Util::throwIfError(hr);
}

void RenderContext_DX11::onSetFrameBufferSize(math::Vec2f newSize) {
  _renderTargetView.reset(nullptr); // release buffer and render target view before resize

  auto hr = _swapChain->ResizeBuffers(0,
                                      static_cast<UINT>(libng::math::max(0.0f, newSize.x)),
                                      static_cast<UINT>(libng::math::max(0.0f, newSize.y)),
                                      DXGI_FORMAT_UNKNOWN,
                                      0);
  Util::throwIfError(hr);
}

void RenderContext_DX11::onBeginRender() {
  auto* ctx = _renderer->d3dDeviceContext();
  if (!_renderTargetView) {
    _createRenderTarget();
  }

  DX11_ID3DRenderTargetView* rt[] = {_renderTargetView};
  // ctx->OMSetRenderTargets(1, rt, _depthStencilView);
  ctx->OMSetRenderTargets(1, rt, nullptr);

  D3D11_VIEWPORT viewport = {};
  viewport.TopLeftX       = 0;
  viewport.TopLeftY       = 0;
  viewport.Width          = _frameBufferSize.x;
  viewport.Height         = _frameBufferSize.y;

  ctx->RSSetViewports(1, &viewport);
}

void RenderContext_DX11::onEndRender() {
}

void RenderContext_DX11::_setTestShaders() {
  HRESULT hr;
  const wchar_t* shaderFile = L"Shaders/hlsl/test.hlsl";

  auto* dev = _renderer->d3dDevice();
  auto* ctx = _renderer->d3dDeviceContext();

  if (!_testVertexShader) {
    ComPtr<ID3DBlob> bytecode;
    ComPtr<ID3DBlob> errorMsg;
    hr = D3DCompileFromFile(shaderFile, 0, 0, "vs_main", "vs_4_0", 0, 0, bytecode.ptrForInit(), errorMsg.ptrForInit());
    Util::throwIfError(hr);

    _testVertexShaderBytecode = bytecode;

    hr = dev->CreateVertexShader(bytecode->GetBufferPointer(),
                                 bytecode->GetBufferSize(),
                                 nullptr,
                                 _testVertexShader.ptrForInit());
    Util::throwIfError(hr);
  }

  if (!_testPixelShader) {
    ComPtr<ID3DBlob> bytecode;
    ComPtr<ID3DBlob> errorMsg;
    hr = D3DCompileFromFile(shaderFile, 0, 0, "ps_main", "ps_4_0", 0, 0, bytecode.ptrForInit(), errorMsg.ptrForInit());
    Util::throwIfError(hr);

    hr = dev->CreatePixelShader(bytecode->GetBufferPointer(),
                                bytecode->GetBufferSize(),
                                nullptr,
                                _testPixelShader.ptrForInit());
    Util::throwIfError(hr);
  }

  if (!_testRasterizerState) {
    D3D11_RASTERIZER_DESC rasterDesc = {};
    rasterDesc.AntialiasedLineEnable = true;
    rasterDesc.CullMode              = D3D11_CULL_NONE;
    rasterDesc.DepthBias             = 0;
    rasterDesc.DepthBiasClamp        = 0.0f;
    rasterDesc.DepthClipEnable       = true;

    bool wireframe      = true;
    rasterDesc.FillMode = wireframe ? D3D11_FILL_WIREFRAME : D3D11_FILL_SOLID;

    rasterDesc.FrontCounterClockwise = true;
    rasterDesc.MultisampleEnable     = false;
    rasterDesc.ScissorEnable         = false;
    rasterDesc.SlopeScaledDepthBias  = 0.0f;

    hr = dev->CreateRasterizerState(&rasterDesc, _testRasterizerState.ptrForInit());
    Util::throwIfError(hr);
  }

  if (!_testDepthStencilState) {
    D3D11_DEPTH_STENCIL_DESC depthStencilDesc = {};
    bool depthTest                            = false;
    if (depthTest) {
      depthStencilDesc.DepthEnable = true;
      depthStencilDesc.DepthFunc   = D3D11_COMPARISON_LESS;
    } else {
      depthStencilDesc.DepthEnable = false;
    }

    depthStencilDesc.DepthWriteMask   = D3D11_DEPTH_WRITE_MASK_ALL;
    depthStencilDesc.StencilEnable    = false;
    depthStencilDesc.StencilReadMask  = 0xFF;
    depthStencilDesc.StencilWriteMask = 0xFF;

    hr = dev->CreateDepthStencilState(&depthStencilDesc, _testDepthStencilState.ptrForInit());
    Util::throwIfError(hr);
  }

  if (!_testBlendState) {
    D3D11_BLEND_DESC blendStateDesc       = {};
    blendStateDesc.AlphaToCoverageEnable  = false;
    blendStateDesc.IndependentBlendEnable = false;
    auto& rtDesc                          = blendStateDesc.RenderTarget[0];

    rtDesc.RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
    bool blendEnable             = true;
    if (blendEnable) {
      rtDesc.BlendEnable    = true;
      rtDesc.BlendOp        = D3D11_BLEND_OP_ADD;
      rtDesc.BlendOpAlpha   = D3D11_BLEND_OP_ADD;
      rtDesc.SrcBlend       = D3D11_BLEND_SRC_ALPHA;
      rtDesc.DestBlend      = D3D11_BLEND_INV_SRC_ALPHA;
      rtDesc.SrcBlendAlpha  = D3D11_BLEND_SRC_ALPHA;
      rtDesc.DestBlendAlpha = D3D11_BLEND_INV_SRC_ALPHA;
    } else {
      rtDesc.BlendEnable = false;
    }

    hr = dev->CreateBlendState(&blendStateDesc, _testBlendState.ptrForInit());
    Util::throwIfError(hr);
  }

  ctx->RSSetState(_testRasterizerState);
  ctx->OMSetDepthStencilState(_testDepthStencilState, 1);

  math::Color4f blendColor(1, 1, 1, 1);
  ctx->OMSetBlendState(_testBlendState, blendColor.data, 0xffffffff);

  ctx->VSSetShader(_testVertexShader, 0, 0);
  ctx->PSSetShader(_testPixelShader, 0, 0);
}

void RenderContext_DX11::onCommit(RenderCommandBuffer& cmdBuf) {
  _dispatch(this, cmdBuf);
}

DX11_ID3DInputLayout* RenderContext_DX11::_getTestInputLayout(const VertexLayout* src) {
  if (!src)
    return nullptr;

  auto it = _testInputLayouts.find(src);
  if (it != _testInputLayouts.end()) {
    return it->second;
  }

  Vector_<D3D11_INPUT_ELEMENT_DESC, 32> inputDesc;

  for (auto& e : src->elements) {
    auto& dst                = inputDesc.emplace_back();
    auto semanticType        = VertexSemanticUtil::getType(e.semantic);
    dst.SemanticName         = Util::getDxSemanticName(semanticType);
    dst.SemanticIndex        = VertexSemanticUtil::getIndex(e.semantic);
    dst.Format               = Util::getDxFormat(e.dataType);
    dst.InputSlot            = 0;
    dst.AlignedByteOffset    = e.offset;
    dst.InputSlotClass       = D3D11_INPUT_PER_VERTEX_DATA;
    dst.InstanceDataStepRate = 0;
  }

  ComPtr<DX11_ID3DInputLayout> outLayout;

  auto* dev = _renderer->d3dDevice();
  auto hr   = dev->CreateInputLayout(inputDesc.data(),
                                   static_cast<UINT>(inputDesc.size()),
                                   _testVertexShaderBytecode->GetBufferPointer(),
                                   _testVertexShaderBytecode->GetBufferSize(),
                                   outLayout.ptrForInit());
  Util::throwIfError(hr);

  _testInputLayouts[src] = outLayout;
  return outLayout;
}

} // namespace libng