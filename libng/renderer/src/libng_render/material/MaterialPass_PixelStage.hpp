#pragma once

#include <libng_render/material/MaterialPass_Stage.hpp>
#include <libng_render/material/ShaderPixelStage.hpp>

namespace libng {

struct MaterialPass_PixelStage : public MaterialPass_Stage {
  using Base = MaterialPass_Stage;

  MaterialPass_PixelStage(MaterialPass* pass, ShaderPixelStage* shaderStage)
    : Base(pass, shaderStage) {
  }
};

} // namespace libng
