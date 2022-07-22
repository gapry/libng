#pragma once

#include <libng_render/material/MaterialPass_Stage.hpp>
#include <libng_render/material/ShaderVertexStage.hpp>

namespace libng {

struct MaterialPass_VertexStage : public MaterialPass_Stage {
  using Base = MaterialPass_Stage;

  MaterialPass_VertexStage(MaterialPass* pass, ShaderVertexStage* shaderStage)
    : Base(pass, shaderStage) {
  }
};

} // namespace libng