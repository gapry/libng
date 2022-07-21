#pragma once

#include <libng_render/material/ShaderStage.hpp>
#include <libng_render/material/ShaderStageMask.hpp>

namespace libng {

struct ShaderPixelStage : public ShaderStage {
  static constexpr ShaderStageMask stageMask() {
    return ShaderStageMask::Pixel;
  }
};

} // namespace libng