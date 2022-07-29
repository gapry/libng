#pragma once

#include <libng_core/math/Vector/Vec2.hpp>
#include <libng_core/math/Vector/Vec3_Basic.hpp>
#include <libng_core/math/Vector/Vec3_SSE.hpp>

namespace libng::math {

#ifndef LIBNG_CPU_SSE
#error
#elif LIBNG_CPU_SSE
template<class T>
using Vec3 = Vec3_SSE<T>;
#else
template<class T>
using Vec3 = Vec3_Basic<T>;
#endif

using Vec3f = Vec3<float>;
using Vec3d = Vec3<double>;

} // namespace libng::math