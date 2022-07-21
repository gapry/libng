#pragma once

#include <libng_render/RendererCommon.hpp>
#include <libng_render/material/ShaderPropType.hpp>

// clang-format off

namespace libng {

struct ShaderPropTypeUtil {
  ShaderPropTypeUtil() = delete;

  using Type = ShaderPropType;

  template<class T> static constexpr Type get();
         template<> static constexpr Type get<i32>      () { return Type::Int;       }
         template<> static constexpr Type get<f32>      () { return Type::Float;     }
         template<> static constexpr Type get<Vec2f>    () { return Type::Vec2f;     }
//       template<> static constexpr Type get<Vec3f>    () { return Type::Vec3f;     }
//       template<> static constexpr Type get<Vec4f>    () { return Type::Vec4f;     }
         template<> static constexpr Type get<Color4f>  () { return Type::Color4f;   }
//       template<> static constexpr Type get<Texture2d>() { return Type::Texture2d; }
};

} // namespace libng