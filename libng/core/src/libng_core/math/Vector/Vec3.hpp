#pragma once

#include <libng_core/math/Vector/Vec2.hpp>
#include <libng_core/math/Vector/Vec3_Basic.hpp>
#include <libng_core/math/Vector/Vec3_SSE.hpp>

namespace libng::math {

template<class T>
using Vec3 = Vec3_Basic<T>;

using Vec3f = Vec3<f32>;
using Vec3d = Vec3<f64>;

} // namespace libng::math