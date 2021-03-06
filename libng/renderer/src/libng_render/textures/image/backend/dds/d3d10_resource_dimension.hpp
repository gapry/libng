#pragma once

namespace libng {

enum D3D10_RESOURCE_DIMENSION : uint32_t
{
  D3D10_RESOURCE_DIMENSION_UNKNOWN   = 0,
  D3D10_RESOURCE_DIMENSION_BUFFER    = 1,
  D3D10_RESOURCE_DIMENSION_TEXTURE1D = 2,
  D3D10_RESOURCE_DIMENSION_TEXTURE2D = 3,
  D3D10_RESOURCE_DIMENSION_TEXTURE3D = 4
};

} // namespace libng