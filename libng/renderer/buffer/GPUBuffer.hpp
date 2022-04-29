#pragma once

#include <types/Object.hpp>
#include <renderer/buffer/GPUBufferType.hpp>
#include <renderer/buffer/GPUBufferCreateDesc.hpp>

namespace libng {

class GPUBuffer : public Object {
public:
  using CreateDesc = GpuBufferCreateDesc;

  GPUBuffer(CreateDesc& desc);

protected:
  CreateDesc _desc;
};

} // namespace libng