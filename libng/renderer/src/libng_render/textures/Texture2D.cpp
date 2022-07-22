#include <libng_render/textures/Texture2D.hpp>

namespace libng {

Texture2D::Texture2D(CreateDesc& desc) {
  LIBNG_LOG("{}\n", __LIBNG_PRETTY_FUNCTION__);

  _type        = DataType::Texture2D;
  _colorType   = desc.colorType;
  _mipmapCount = desc.mipmapCount;
  _size        = desc.size;
}

} // namespace libng