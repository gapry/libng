#pragma once

#include <libng_core/types/enum.hpp>
#include <libng_core/types/number.hpp>

namespace libng::math {

#define ColorElementType_ENUM_LIST(E) \
  E(None, )                           \
  E(UNorm8, )                         \
  E(UNorm16, )                        \
  E(Float32, )                        \
  E(Float64, )                        \
//-------
LIBNG_ENUM_CLASS(ColorElementType, u8);

// clang-format off
template<class T> constexpr ColorElementType ColorElementType_get();
template<>        constexpr ColorElementType ColorElementType_get<u8 >() { return ColorElementType::UNorm8;  }
template<>        constexpr ColorElementType ColorElementType_get<u16>() { return ColorElementType::UNorm16; }
template<>        constexpr ColorElementType ColorElementType_get<f32>() { return ColorElementType::Float32; }
template<>        constexpr ColorElementType ColorElementType_get<f64>() { return ColorElementType::Float64; }

} // namespace libng::math