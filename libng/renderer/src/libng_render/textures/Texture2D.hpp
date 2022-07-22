#pragma once

#include <libng_render/RendererCommon.hpp>
#include <libng_render/textures/Texture.hpp>
#include <libng_render/textures/Texture2D_CreateDesc.hpp>

namespace libng {

class Texture2D : public Texture {
  using Vec2i     = math::Vec2i;
  using ColorType = math::ColorType;

public:
  using CreateDesc = Texture2D_CreateDesc;

  // clang-format off
  ColorType colorType  () const { return _colorType;   }
  int       mipmapCount() const { return _mipmapCount; }
  int       width      () const { return _size.x;      }
  int       height     () const { return _size.y;      }
  Vec2i     size       () const { return _size;        }
  // clang-format on

protected:
  Texture2D(CreateDesc& desc);

  ColorType _colorType = ColorType::None;
  int _mipmapCount     = 0;
  Vec2i _size{0, 0};
};

} // namespace libng