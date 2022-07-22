#include <libng_render/textures/image/backend/ddsLoader.hpp>

namespace libng {

ddsLoader::ddsLoader() {
  LIBNG_LOG("{}\n", __LIBNG_PRETTY_FUNCTION__);
}

ddsLoader::~ddsLoader() {
  LIBNG_LOG("{}\n", __LIBNG_PRETTY_FUNCTION__);
}

void ddsLoader::Reader::_readHeader(binary_deserializer& de, DDS_HEADER& hdr) {
  de.io_fixed_le(hdr.dwSize);
  de.io_fixed_le(hdr.dwHeaderFlags);
  de.io_fixed_le(hdr.dwHeight);
  de.io_fixed_le(hdr.dwWidth);
  de.io_fixed_le(hdr.dwPitchOrLinearSize);
  de.io_fixed_le(hdr.dwDepth);
  de.io_fixed_le(hdr.dwMipMapCount);
  de.advance(sizeof(hdr.dwReserved1[0]) * 11);

  de.io_fixed_le(hdr.ddspf.dwSize);
  de.io_fixed_le(hdr.ddspf.dwFlags);
  de.io_fixed_le(hdr.ddspf.dwFourCC);
  de.io_fixed_le(hdr.ddspf.dwRGBBitCount);
  de.io_fixed_le(hdr.ddspf.dwRBitMask);
  de.io_fixed_le(hdr.ddspf.dwGBitMask);
  de.io_fixed_le(hdr.ddspf.dwBBitMask);
  de.io_fixed_le(hdr.ddspf.dwABitMask);

  de.io_fixed_le(hdr.dwSurfaceFlags);
  de.io_fixed_le(hdr.dwCubemapFlags);
  de.advance(sizeof(hdr.dwReserved2[0]) * 3);

  if (hdr.dwSize != sizeof(hdr)) {
    throw LIBNG_ERROR("DDS invalid header size");
  }

  if (hdr.ddspf.dwSize != sizeof(DDS_PIXELFORMAT)) {
    throw LIBNG_ERROR("DDS invalid header pixel format size");
  }

  if (!(hdr.ddspf.dwFlags & DDS_FOURCC)) {
    throw LIBNG_ERROR("DDS invalid header pixel format");
  }
}

void ddsLoader::Reader::_readHeader10(binary_deserializer& de, DDS_HEADER_DXT10& hdr10) {
  uint32_t tmp32;

  de.io_fixed_le(tmp32);
  hdr10.dxgiFormat = static_cast<DXGI_FORMAT>(tmp32);

  de.io_fixed_le(tmp32);
  hdr10.resourceDimension = static_cast<D3D10_RESOURCE_DIMENSION>(tmp32);

  de.io_fixed_le(hdr10.miscFlag);
  de.io_fixed_le(hdr10.arraySize);
  de.io_fixed_le(hdr10.miscFlags2);
}

void ddsLoader::Reader::load(Image& img, ByteSpan data, ColorType expectType) {
  binary_deserializer de(data);

  uint32_t sign;
  de.io_fixed_le(sign);

  if (sign != FourCC("DDS ")) {
    throw LIBNG_ERROR("Erros DDS file signature");
  }

  DDS_HEADER hdr;
  _readHeader(de, hdr);

  auto colorType = ColorType::None;

  if (hdr.ddspf.dwFourCC == FourCC("DX10")) {
    DDS_HEADER_DXT10 hdr10;
    _readHeader10(de, hdr10);

    if (hdr10.resourceDimension != D3D10_RESOURCE_DIMENSION_TEXTURE2D) {
      throw LIBNG_ERROR("Erros DDS texture dimension");
    }

    switch (hdr10.dxgiFormat) {
      case DXGI_FORMAT_BC1_UNORM: colorType = ColorType::BC1; break;
      case DXGI_FORMAT_BC2_UNORM: colorType = ColorType::BC2; break;
      case DXGI_FORMAT_BC3_UNORM: colorType = ColorType::BC3; break;
      case DXGI_FORMAT_BC4_UNORM: colorType = ColorType::BC4; break;
      case DXGI_FORMAT_BC5_UNORM: colorType = ColorType::BC5; break;
      case DXGI_FORMAT_BC7_UNORM: colorType = ColorType::BC7; break;
      default: throw LIBNG_ERROR("Erros DDS10 file color format");
    }
  } else {
    switch (hdr.ddspf.dwFourCC) {
      case FourCC("DXT1"): colorType = ColorType::BC1; break;
      case FourCC("DXT2"): colorType = ColorType::BC2; break;
      case FourCC("DXT3"): colorType = ColorType::BC2; break;
      case FourCC("DXT4"): colorType = ColorType::BC3; break;
      case FourCC("DXT5"): colorType = ColorType::BC3; break;

      case FourCC("BC4U"): colorType = ColorType::BC4; break;
      case FourCC("BC5U"): colorType = ColorType::BC5; break;
      case FourCC("DXT7"): colorType = ColorType::BC7; break;
      default: throw LIBNG_ERROR("Erros DDS file color format");
    }
  }

  if (hdr.dwWidth % 4 || hdr.dwHeight % 4) {
    throw LIBNG_ERROR("Erros DDS file width and height must be multiples of 4");
  }

  int mipmapCount = 1;

  if (hdr.dwMipMapCount > 1) {
    uint32_t w = hdr.dwWidth;
    uint32_t h = hdr.dwHeight;
    for (uint32_t i = 0; i < hdr.dwMipMapCount; i++) {
      if (w & 0x3 || h & 0x3) {
        break; // bypass non-multiple of 4 level
      }
      w >>= 1;
      h >>= 1;
      mipmapCount = i + 1;
    }
  }

  int blockSize     = ColorUtil::bytesPerPixelBlock(colorType);
  int strideInBytes = math::max(1U, ((hdr.dwWidth + 3) / 4)) * blockSize;

  img.create(colorType, hdr.dwWidth, hdr.dwHeight, strideInBytes, mipmapCount, de.remain());
  img.copyToPixelData(ByteSpan(de.cur(), de.remain()));
}

} // namespace libng