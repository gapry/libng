#pragma once

#include <libng_render/textures/image/backend/dds/d3d10_resource_dimension.hpp>
#include <libng_render/textures/image/backend/dds/dxgi_format.hpp>

namespace libng {

// clang-format off
struct DDS_HEADER_DXT10 {
  DXGI_FORMAT              dxgiFormat;
  D3D10_RESOURCE_DIMENSION resourceDimension;
  uint32_t                 miscFlag;
  uint32_t                 arraySize;
  uint32_t                 miscFlags2;
};

} // namespace libng