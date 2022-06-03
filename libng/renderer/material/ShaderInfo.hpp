#pragma once

#include <renderer/material/ShaderPropType.hpp>

namespace libng {

struct ShaderInfo {
  struct Prop {
    ShaderPropType propType = ShaderPropType::None;
  };
};

} // namespace libng
