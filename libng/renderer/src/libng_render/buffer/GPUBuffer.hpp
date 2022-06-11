#pragma once

#include <libng_core/types/Object.hpp>
#include <libng_core/types/number.hpp>
#include <libng_render/buffer/GPUBufferType.hpp>
#include <libng_render/buffer/GPUBufferCreateDesc.hpp>

namespace libng {

class GPUBuffer : public Object {
public:
  using CreateDesc = GPUBufferCreateDesc;
  using Type       = GPUBufferType;

  GPUBuffer(CreateDesc& desc);

  void uploadToGPU(Span<const u8> data, size_t offset = 0);

protected:
  virtual void onUploadToGPU(Span<const u8> data, size_t offset) = 0;

  CreateDesc _desc;
};

} // namespace libng
