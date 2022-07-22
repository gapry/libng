#pragma once

#include <libng_render/RendererCommon.hpp>
#include <libng_render/textures/image/ImageInfo.hpp>

namespace libng {

// clang-format off
class Image : public NonCopyable {
  using Vec2i     = math::Vec2i;
  using ColorType = math::ColorType;
  using ColorUtil = math::ColorUtil;

public:
  using Info = ImageInfo;

  Image();
  Image(Image&& r);

  ~Image();

  void operator=(Image&& r);

  void clear();

  void loadFile(StrView filename);

  void loadPngFile(StrView filename);
  void loadPngMem (ByteSpan data);

  void loadDdsFile(StrView filename);
  void loadDdsMem (ByteSpan data);

  void create(ColorType colorType, int width, int height);
  void create(ColorType colorType, int width, int height, int strideInBytes);
  void create(ColorType colorType, int width, int height, int strideInBytes, int mipmapCount, size_t dataSizeInBytes);

  LIBNG_INLINE const Info&  info()          const { return _info;               }
  LIBNG_INLINE const Vec2i& size()          const { return _info.size;          }
  LIBNG_INLINE int          strideInBytes() const { return _info.strideInBytes; }
  LIBNG_INLINE int          width()         const { return _info.size.x;        }
  LIBNG_INLINE int          height()        const { return _info.size.y;        }
  LIBNG_INLINE ColorType    colorType()     const { return _info.colorType;     }

  template<class COLOR> LIBNG_INLINE const COLOR& pixel(int x, int y) const { return row<COLOR>(y)[x]; }
  template<class COLOR> LIBNG_INLINE       COLOR& pixel(int x, int y)       { return row<COLOR>(y)[x]; }

  template<class COLOR> LIBNG_INLINE Span<      COLOR> row(int y)       { _checkType(COLOR::kColorType); return row_noCheck<COLOR>(y); }
  template<class COLOR> LIBNG_INLINE Span<const COLOR> row(int y) const { _checkType(COLOR::kColorType); return row_noCheck<COLOR>(y); }

  template<class COLOR> LIBNG_INLINE Span<      COLOR> row_noCheck(int y)       { return Span<      COLOR>(reinterpret_cast<      COLOR*>(rowBytes(y).data()), _info.size.x); }
  template<class COLOR> LIBNG_INLINE Span<const COLOR> row_noCheck(int y) const { return Span<const COLOR>(reinterpret_cast<const COLOR*>(rowBytes(y).data()), _info.size.x); }

  LIBNG_INLINE Span<      u8> rowBytes(int y)       { return Span<      u8>(&_pixelData[y * _info.strideInBytes], _info.size.x * _info.pixelSizeInBytes()); }
  LIBNG_INLINE Span<const u8> rowBytes(int y) const { return Span<const u8>(&_pixelData[y * _info.strideInBytes], _info.size.x * _info.pixelSizeInBytes()); }

  const void* dataPtr() const {
    return _pixelData.data();
  }

  void copyToPixelData(ByteSpan src) {
    _pixelData.assign(src.begin(), src.end());
  }

  template<class COLOR>
  void fill(const COLOR& color);

private:
  void _create(ColorType colorType,     
               int       width,               
               int       height,              
               int       strideInBytes,       
               int       mipmapCount,         
               size_t    dataSizeInBytes); 

  void _checkType(ColorType colorType) const {
    if (colorType != _info.colorType) {
      throw LIBNG_ERROR("{}\n", "Invalid ColorType");
    }
  }

  Info _info;
  Vector<u8> _pixelData;
};

// clang-format on

template<class COLOR>
LIBNG_INLINE void Image::fill(const COLOR& color) {
  _checkType(COLOR::kColorType);
  for (int y = 0; y < _info.size.y; y++) {
    for (auto& p : row_noCheck<COLOR>(y)) {
      p = color;
    }
  }
}

} // namespace libng