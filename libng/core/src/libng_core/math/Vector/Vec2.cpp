#pragma once

#include <libng_core/math/Vector/Vec2.hpp>

namespace libng::math {

#if LIBNG_MATH_USE
#else
template Vec2_Basic<f32>;
template Vec2_Basic<f64>;
#endif

} // namespace libng::math