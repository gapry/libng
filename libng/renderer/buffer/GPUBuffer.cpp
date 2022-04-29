#pragma once

#include <renderer/buffer/GPUBuffer.hpp>

namespace libng {

GPUBuffer::GPUBuffer(CreateDesc& desc)
  : _desc(desc) {
}

} // namespace libng