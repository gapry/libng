#pragma once

#include <libpng16/png.h>

#include <libng_render/RendererCommon.hpp>
#include <libng_render/textures/image/Image.hpp>

namespace libng {

class pngLoader {
  using ColorUtil        = math::ColorUtil;
  using ColorType        = math::ColorType;
  using ColorModel       = math::ColorModel;
  using ColorElementType = math::ColorElementType;

public:
  pngLoader();
  ~pngLoader();

  class Reader {
  public:
    static void s_onRead(png_structp png, png_bytep dest, png_size_t len);

    ~Reader();

    void load(Image& img, ByteSpan data, ColorType expectType = ColorType::None);

    void onRead(png_bytep dest, png_size_t len);

    void setReadFilter(ColorType out_type, int in_type, int in_bit, bool in_palette_has_alpha);

    bool error_longjmp_restore_point();

    png_structp _png{nullptr};
    png_infop _info{nullptr};

    ByteSpan _data;
    const u8* _readPtr = nullptr;
  };

  class Writer {
  public:
  };
};

} // namespace libng