#pragma once

#include <libng_render/RendererCommon.hpp>

#include <libng_render/textures/Texture2D.hpp>
#include <libng_render/textures/Texture2D_CreateDesc.hpp>

#include <libng_render/backend/dx11/Util_DX11.hpp>

namespace libng {

class Texture2D_DX11 : public Texture2D {
  using Base      = Texture2D;
  using Util      = Util_DX11;
  using ColorType = math::ColorType;

public:
  Texture2D_DX11(CreateDesc& desc);
  ~Texture2D_DX11();

  DX11_ID3DShaderResourceView* resourceView() {
    return _resourceView.ptr();
  }

  DX11_ID3DSamplerState* samplerState() {
    return _samplerState.ptr();
  }

private:
  ComPtr<DX11_ID3DTexture2D> _tex;
  ComPtr<DX11_ID3DShaderResourceView> _resourceView;
  ComPtr<DX11_ID3DSamplerState> _samplerState;
};

} // namespace libng
