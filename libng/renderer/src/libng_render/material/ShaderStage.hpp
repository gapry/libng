#pragma once

#include <libng_render/RendererCommon.hpp>
#include <libng_render/material/ShaderStageInfo.hpp>

namespace libng {

struct ShaderStage : public NonCopyable {
  const ShaderStageInfo* info() const {
    return &_info;
  }

protected:
  ShaderStageInfo _info;
};

} // namespace libng