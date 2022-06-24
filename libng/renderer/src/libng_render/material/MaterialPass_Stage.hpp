#pragma once

#include <libng_core/types/noncopyable.hpp>

#include <libng_render/material/MaterialPass.hpp>
#include <libng_render/material/ShaderStageInfo.hpp>

namespace libng {

struct MaterialPass_Stage : public NonCopyable {
  using Pass = MaterialPass;

  friend class MaterialPass;

protected:
  struct ConstBuffer {
    using DataType = ShaderStageInfo::DataType;
    using Info     = ShaderStageInfo::ConstBuffer;
    using VarInfo  = ShaderStageInfo::Variable;
  };
};

} // namespace libng