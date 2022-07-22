#pragma once

#include <libng_render/textures/image/backend/dds/dds_pixel_format.hpp>

namespace libng {

struct DDS_HEADER {
  using dds_pfmt = DDS_PIXELFORMAT;

  uint32_t dwSize;              //
  uint32_t dwHeaderFlags;       //
  uint32_t dwHeight;            //
  uint32_t dwWidth;             //
  uint32_t dwPitchOrLinearSize; //
  uint32_t dwDepth;             // only if DDS_HEADER_FLAGS_VOLUME is set in dwHeaderFlags
  uint32_t dwMipMapCount;       //
  uint32_t dwReserved1[11];     //
  dds_pfmt ddspf;               //
  uint32_t dwSurfaceFlags;      //
  uint32_t dwCubemapFlags;      //
  uint32_t dwReserved2[3];      //
};

} // namespace libng