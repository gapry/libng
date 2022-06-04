#pragma once

#include <libcxx/string.hpp>
#include <libcxx/fixed_vector.hpp>

#include <renderer/material/ShaderPropType.hpp>

namespace libng {

struct ShaderInfo {
  struct Prop {
    ShaderPropType propType = ShaderPropType::None;

    String name;
    String displayName;
    String defaultValue;
  };

  struct Pass {
    String name;
    String vsFunc;
    String psFunc;
  };

  Vector_<Prop, 8> props;
  Vector_<Pass, 1> passes;

  void clear();
};

} // namespace libng
