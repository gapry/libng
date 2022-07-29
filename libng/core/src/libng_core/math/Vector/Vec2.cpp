#pragma once

#include <libng_core/math/Vector/Vec2.hpp>
#include <libng_core/platform/sse.hpp>

namespace libng::math {

#ifndef LIBNG_CPU_SSE
#error
#elif LIBNG_CPU_SSE
template Vec2_SSE<float>;
template Vec2_SSE<double>;
#else
template Vec2_Basic<f32>;
template Vec2_Basic<f64>;
#endif

} // namespace libng::math