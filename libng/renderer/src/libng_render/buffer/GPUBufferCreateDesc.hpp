#pragma once

#include <libng_render/buffer/GPUBufferType.hpp>

namespace libng {

struct GPUBufferCreateDesc {
  using Type = GPUBufferType;

  Type type         = Type::None;
  size_t bufferSize = 0;
  size_t stride     = 16;
};

} // namespace libng