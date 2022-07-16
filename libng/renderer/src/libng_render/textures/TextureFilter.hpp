#pragma once

#include <libng_render/RendererCommon.hpp>

namespace libng {

#define TextureFilter_ENUM_LIST(E)                                \
  E(None, )                                                       \
  E(Point, )       /* 1 texels on closest mimap level          */ \
  E(Linear, )      /* 1 texels on 2 mipmap levels              */ \
  E(Bilinear, )    /* 4 texels on closest mipmap level         */ \
  E(Trilinear, )   /* 4 texels on 2 mipmap levels              */ \
  E(Anisotropic, ) /* https://en.wikipedia.org/wiki/Anisotropy */ \
  E(_END, )                                                       \
//----
LIBNG_ENUM_CLASS(TextureFilter, u8);

} // namespace libng