#pragma once

#include <libng_render/textures/Image.hpp>
#include <libng_render/textures/SamplerState.hpp>
#include <libng_render/textures/Texture_CreateDesc.hpp>

namespace libng {

struct Texture2D_CreateDesc : public Texture_CreateDesc {
public:
  Texture2D_CreateDesc();
  ~Texture2D_CreateDesc();

  // clang-format off
  Vec2i size   {0, 0};
  SamplerState sampleState;
  Image        imageToUpload;
};

}