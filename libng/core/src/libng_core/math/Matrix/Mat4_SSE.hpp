#pragma once

#include <libng_core/math/Matrix/Mat4_Basic.hpp>
#include <libng_core/platform/sse.hpp>

namespace libng::math {

template<class T>
using Mat4_SSE_Data = Mat4_Basic_Data<T>;

using Mat4f_SSE_Data = Mat4_SSE_Data<float>;
using Mat4d_SSE_Data = Mat4_SSE_Data<double>;

template<class T>
struct Mat4_SSE_Select {
  using Data = Mat4_Basic_Data<T>;
};
// template<> struct Mat4_SSE_Select<float > { using Data = Mat4f_SSE_Data; };
// template<> struct Mat4_SSE_Select<double> { using Data = Mat4d_SSE_Data; };

template<class T>
using Mat4_SSE = Mat4_Basic<T, typename Mat4_SSE_Select<T>::Data>;

using Mat4f_SSE = Mat4_SSE<float>;
using Mat4d_SSE = Mat4_SSE<double>;

} // namespace libng::math