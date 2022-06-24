#pragma once

#include <libng_core/types/RefCountBase.hpp>

#include <libng_render/material/MaterialPass.hpp>
#include <libng_render/material/MaterialPass_PixelStage.hpp>
#include <libng_render/material/MaterialPass_Stage.hpp>
#include <libng_render/material/MaterialPass_VertexStage.hpp>

namespace libng {

class MaterialPass : public RefCountBase {
public:
  using Pass        = MaterialPass;
  using Stage       = MaterialPass_Stage;
  using VertexStage = MaterialPass_VertexStage;
  using PixelStage  = MaterialPass_PixelStage;
};

} // namespace libng