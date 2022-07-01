#pragma once

#include <libng_core/math/Matrix/Mat4_Basic.hpp>
#include <libng_core/math/Matrix/Mat4_SSE.hpp>
#include <libng_core/platform/sse.hpp>

namespace libng {

#if LIBNG_MATH_SSE
#else
template<class T>
using Mat4 = Mat4_Basic<T>;
#endif

using Mat4f = Mat4<float>;
using Mat4d = Mat4<double>;

} // namespace libng