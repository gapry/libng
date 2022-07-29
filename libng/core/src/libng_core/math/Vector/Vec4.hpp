#pragma once

#include <libng_core/math/Vector/Vec4_Basic.hpp>
#include <libng_core/math/Vector/Vec4_SSE.hpp>

namespace libng::math {

#ifndef LIBNG_CPU_SSE
#error
#elif LIBNG_CPU_SSE
template<class T>
using Vec4 = Vec4_SSE<T>;
#else
template<class T>
using Vec4 = Vec4_Basic<T>;
#endif

using Vec4f = Vec4<float>;
using Vec4d = Vec4<double>;

} // namespace libng::math