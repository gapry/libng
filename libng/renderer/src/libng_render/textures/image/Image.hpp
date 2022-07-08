#pragma once

#include <libng_render/RendererCommon.hpp>
#include <libng_render/textures/image/ImageInfo.hpp>

namespace libng {

class Image : public NonCopyable {
public:
  using Info = ImageInfo;

  Image();
  ~Image();

private:
  Info _info;
};

} // namespace libng