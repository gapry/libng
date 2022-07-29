#pragma once

#include <libng_core/math/Matrix/Mat4_Basic.hpp>
#include <libng_core/math/Matrix/Mat4_SSE.hpp>

namespace libng::math {

#ifndef LIBNG_CPU_SSE
#error
#elif LIBNG_CPU_SSE
template<class T>
using Mat4 = Mat4_SSE<T>;
#else
template<class T>
using Mat4 = Mat4_Basic<T>;
#endif

using Mat4f = Mat4<float>;
using Mat4d = Mat4<double>;

} // namespace libng::math