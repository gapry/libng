#pragma once

#include <libng_core/types/enum.hpp>
#include <libng_core/types/number.hpp>

namespace libng::math {

#define ColorElementType_ENUM_LIST(E) \
  E(None, )                           \
  E(UNorm8, )                         \
  E(UNorm16, )                        \
  E(Float16, )                        \
  E(Float32, )                        \
  E(Float64, )                        \
//-------
LIBNG_MATH_ENUM_CLASS(ColorElementType, u8);

// clang-format off
template<class T> constexpr libng::math::ColorElementType ColorElementType_get();
template<>        constexpr libng::math::ColorElementType ColorElementType_get<u8 >() { return libng::math::ColorElementType::UNorm8;  }
template<>        constexpr libng::math::ColorElementType ColorElementType_get<u16>() { return libng::math::ColorElementType::UNorm16; }
template<>        constexpr libng::math::ColorElementType ColorElementType_get<f16>() { return libng::math::ColorElementType::Float16; }
template<>        constexpr libng::math::ColorElementType ColorElementType_get<f32>() { return libng::math::ColorElementType::Float32; }
template<>        constexpr libng::math::ColorElementType ColorElementType_get<f64>() { return libng::math::ColorElementType::Float64; }

} // namespace libng::math