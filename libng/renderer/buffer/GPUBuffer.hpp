#pragma once

#include <types/Object.hpp>
#include <types/number.hpp>
#include <libcxx/util/util.hpp>

#include <renderer/buffer/GPUBufferType.hpp>
#include <renderer/buffer/GPUBufferCreateDesc.hpp>

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
