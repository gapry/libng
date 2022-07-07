#pragma once

#include <libng_core/types/noncopyable.hpp>

#include <libng_render/material/MaterialPass.hpp>
#include <libng_render/material/ShaderStageInfo.hpp>

namespace libng {

struct MaterialPass_Stage : public NonCopyable {
  MaterialPass_Stage() = default;
};

} // namespace libng