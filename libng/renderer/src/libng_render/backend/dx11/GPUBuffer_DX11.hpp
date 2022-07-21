#pragma once

#include <libng_render/RendererCommon.hpp>

#include <libng_render/buffer/GPUBuffer.hpp>

#include <libng_render/backend/dx11/Type_DX11.hpp>
#include <libng_render/backend/dx11/Util_DX11.hpp>

namespace libng {

class GPUBuffer_DX11 : public GPUBuffer {
  using Base = GPUBuffer;
  using Util = Util_DX11;

public:
  GPUBuffer_DX11(CreateDesc& desc);

  virtual void onUploadToGPU(Span<const u8> data, size_t offset) override;

  DX11_ID3DBuffer* d3dBuf() {
    return _d3dBuf;
  }

private:
  ComPtr<DX11_ID3DBuffer> _d3dBuf;
};

} // namespace libng