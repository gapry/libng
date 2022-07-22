#include <libng_render/textures/image/Image.hpp>

namespace libng {

Image::Image() {
  LIBNG_LOG("{}\n", __LIBNG_PRETTY_FUNCTION__);
}

Image::Image(Image&& rhs) {
  LIBNG_LOG("{}\n", __LIBNG_PRETTY_FUNCTION__);
}

Image::~Image() {
  LIBNG_LOG("{}\n", __LIBNG_PRETTY_FUNCTION__);
}

void Image::operator=(Image&& rhs) {
  LIBNG_LOG("{}\n", __LIBNG_PRETTY_FUNCTION__);
}

void Image::clear() {
  _info = ImageInfo();
  _pixelData.clear();
}

void Image::loadFile(StrView filename) {
}

void Image::loadPngFile(StrView filename) {
  MemMapFile mm;
  mm.open(filename);
  loadPngMem(mm);
}

void Image::loadPngMem(ByteSpan data) {
}

void Image::loadDdsFile(StrView filename) {
  MemMapFile mm;
  mm.open(filename);
  loadDdsMem(mm);
}

void Image::loadDdsMem(ByteSpan data) {
}

void Image::create(ColorType colorType, int width, int height) {
  create(colorType, width, height, width * ColorUtil::pixelSizeInBytes(colorType));
}

void Image::create(ColorType colorType, int width, int height, int strideInBytes) {
  _create(colorType, width, height, strideInBytes, 1, strideInBytes * height);
}

void Image::create(ColorType colorType,
                   int width,
                   int height,
                   int strideInBytes,
                   int mipmapCount,
                   size_t dataSizeInBytes) {
  _create(colorType, width, height, strideInBytes, mipmapCount, dataSizeInBytes);
}

void Image::_create(ColorType colorType,
                    int width,
                    int height,
                    int strideInBytes,
                    int mipmapCount,
                    size_t dataSizeInBytes) {
  _info.colorType = colorType;
  _info.size.set(width, height);
  _info.strideInBytes = strideInBytes;
  _info.mipmapCount   = mipmapCount;

  try {
    _pixelData.clear();
    _pixelData.resize(dataSizeInBytes);
  } catch (...) {
    clear();
    throw;
  }
}

} // namespace libng