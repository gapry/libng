#pragma once

#include <libng_core/memory/ComPtr.hpp>
#include <libng_render/backend/dx11/DX11Util.hpp>
#include <libng_render/backend/dx11/TypeDX11.hpp>
#include <libng_render/buffer/GPUBuffer.hpp>

namespace libng {

class GPUBufferDX11 : public GPUBuffer {
  using Base = GPUBuffer;
  using Util = DX11Util;

public:
  GPUBufferDX11(CreateDesc& desc);

  virtual void onUploadToGPU(Span<const u8> data, size_t offset) override;

  DX11_ID3DBuffer* d3dBuf() {
    return _d3dBuf;
  }

private:
  ComPtr<DX11_ID3DBuffer> _d3dBuf;
};

} // namespace libng