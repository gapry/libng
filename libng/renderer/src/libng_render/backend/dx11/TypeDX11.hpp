#pragma once

#include <libng_core/platform/graphics.hpp>

#if LIBNG_RENDER_DX11

namespace libng {

using DX11_IDXGIFactory   = IDXGIFactory1;
using DX11_IDXGIDevice    = IDXGIDevice;
using DX11_IDXGIAdapter   = IDXGIAdapter3;
using DX11_IDXGISwapChain = IDXGISwapChain;

using DX11_ID3DDevice        = ID3D11Device1;
using DX11_ID3DDeviceContext = ID3D11DeviceContext4;
using DX11_ID3DDebug         = ID3D11Debug;

using DX11_ID3DTexture1D = ID3D11Texture1D;
using DX11_ID3DTexture2D = ID3D11Texture2D;
using DX11_ID3DTexture3D = ID3D11Texture3D;

using DX11_ID3DRenderTargetView = ID3D11RenderTargetView;
using DX11_ID3DDepthStencilView = ID3D11DepthStencilView;

using DX11_ID3DBuffer = ID3D11Buffer;
using DX11_ID3DBlob   = ID3DBlob;

using DX11_ID3DVertexShader = ID3D11VertexShader;
using DX11_ID3DPixelShader  = ID3D11PixelShader;
using DX11_ID3DInputLayout  = ID3D11InputLayout;

using DX11_ID3DRasterizerState   = ID3D11RasterizerState;
using DX11_ID3DDepthStencilState = ID3D11DepthStencilState;
using DX11_ID3DBlendState        = ID3D11BlendState;

} // namespace libng

#endif