#include <libng_render/backend/dx11/Texture2D_DX11.hpp>

namespace libng {

Texture2D_DX11::Texture2D_DX11(CreateDesc& desc)
  : Base(desc) {
  LIBNG_LOG("{}\n", __LIBNG_PRETTY_FUNCTION__);
}

Texture2D_DX11::~Texture2D_DX11() {
  LIBNG_LOG("{}\n", __LIBNG_PRETTY_FUNCTION__);
}

} // namespace libng