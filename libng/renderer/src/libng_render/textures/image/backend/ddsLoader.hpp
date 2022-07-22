#pragma once

#include <libng_render/RendererCommon.hpp>
#include <libng_render/textures/image/Image.hpp>
#include <libng_render/textures/image/backend/dds/dds.hpp>

namespace libng {

class ddsLoader {
  using ColorUtil        = math::ColorUtil;
  using ColorType        = math::ColorType;
  using ColorModel       = math::ColorModel;
  using ColorElementType = math::ColorElementType;

public:
  ddsLoader();
  ~ddsLoader();

  class Reader {
  public:
    void load(Image& img, ByteSpan data, ColorType expectType = ColorType::None);

  private:
    void _readHeader(binary_deserializer& de, DDS_HEADER& hdr);
    void _readHeader10(binary_deserializer& de, DDS_HEADER_DXT10& hdr10);
  };

  class Writer {
  public:
  };
};

} // namespace libng