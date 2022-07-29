#pragma once

#include <libng_core/platform/sse.hpp>
#include <libng_core/types/number.hpp>

#include <libng_core/math/Vector/Vec2.hpp>
#include <libng_core/math/Vector/Vec2_Basic.hpp>
#include <libng_core/math/Vector/Vec2_SSE.hpp>

namespace libng::math {

#ifndef LIBNG_CPU_SSE
#error
#elif LIBNG_CPU_SSE
template<class T>
using Vec2 = Vec2_SSE<T>;
#else
template<class T>
using Vec2 = Vec2_Basic<T>;
#endif

using Vec2i = Vec2<i32>;
using Vec2f = Vec2<f32>;
using Vec2d = Vec2<f64>;

} // namespace libng::math