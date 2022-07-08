#include <libng_render/textures/Texture2D.hpp>

namespace libng {

Texture2D::Texture2D(CreateDesc& desc) {
  LIBNG_LOG("{}\n", __LIBNG_PRETTY_FUNCTION__);
}

Texture2D::~Texture2D() {
  LIBNG_LOG("{}\n", __LIBNG_PRETTY_FUNCTION__);
}

} // namespace libng