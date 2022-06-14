#pragma once

#include <libng_core/types/function.hpp>
#include <libng_core/libcxx/string.hpp>
#include <libng_core/libcxx/fixed_vector.hpp>
#include <libng_render/material/ShaderPropType.hpp>

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

  template<class SE>
  void on_json(SE& se) {
    LIBNG_LOG("{}\n", __LIBNG_FUNCTION__);
  }
};

} // namespace libng
