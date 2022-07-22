#pragma once

#include <libng_render/material/RenderState.hpp>
#include <libng_render/material/ShaderPropType.hpp>

namespace libng {

struct ShaderInfo {
  struct Prop {
    ShaderPropType propType = ShaderPropType::None;

    String name;
    String displayName;
    String defaultValue;

    template<class SE>
    void on_json(SE& se) {
      LIBNG_NAMED_IO(se, name);
      LIBNG_NAMED_IO(se, displayName);
      LIBNG_NAMED_IO(se, defaultValue);
    }
  };

  struct Pass {
    String name;
    String vsFunc;
    String psFunc;
    RenderState renderState;

    template<class SE>
    void on_json(SE& se) {
      LIBNG_NAMED_IO(se, name);
      LIBNG_NAMED_IO(se, vsFunc);
      LIBNG_NAMED_IO(se, psFunc);
      LIBNG_NAMED_IO(se, renderState);
    }
  };

  Vector_<Prop, 8> props;
  Vector_<Pass, 1> passes;

  void clear();

  template<class SE>
  void on_json(SE& se) {
    LIBNG_NAMED_IO(se, props);
    LIBNG_NAMED_IO(se, passes);
  }
};

} // namespace libng
