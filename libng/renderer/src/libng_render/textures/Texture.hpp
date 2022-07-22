#pragma once

#include <libng_render/RendererCommon.hpp>
#include <libng_render/textures/Texture_CreateDesc.hpp>
#include <libng_render/type/RenderDataType.hpp>

namespace libng {

class Texture : public RefCountBase {
public:
  using CreateDesc = Texture_CreateDesc;
  using DataType   = RenderDataType;

  DataType type() const {
    return _type;
  }

protected:
  Texture();
  ~Texture();

  DataType _type = DataType::None;
};

} // namespace libng