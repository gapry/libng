#pragma once

#include <libng_render/material/MaterialPass.hpp>
#include <libng_render/material/MaterialPass_Stage.hpp>

namespace libng {

class MaterialPass : public RefCountBase {
public:
  using Pass  = MaterialPass;
  using Stage = MaterialPass_Stage;
};

} // namespace libng