#pragma once

#include <libng_render/RendererCommon.hpp>

namespace libng {

class Texture : public RefCountBase {
public:
  Texture();
  ~Texture();
};

} // namespace libng