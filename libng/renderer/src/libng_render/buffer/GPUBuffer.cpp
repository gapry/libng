#pragma once

#include <libng_render/buffer/GPUBuffer.hpp>

namespace libng {

GPUBuffer::GPUBuffer(CreateDesc& desc)
  : _desc(desc) {
}

/**
 * @brief public member function
 *
 * 1. check the bound size
 * 2. call the protected virtual function
 *
 * @param data
 * @param offset
 */
void GPUBuffer::uploadToGPU(Span<const u8> data, size_t offset) {
  if (data.size() + offset > _desc.bufferSize) {
    throw LIBNG_ERROR("[error] The input data of GPU Buffer is out of range");
  }
  onUploadToGPU(data, offset);
}

} // namespace libng