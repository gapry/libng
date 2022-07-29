#include <libng_core/math/Matrix/Mat4.hpp>

namespace libng::math {

#ifndef LIBNG_CPU_SSE
#error
#elif LIBNG_CPU_SSE
template Mat4_SSE<float>;
template Mat4_SSE<double>;
#else
template Mat4_Basic<float>;
template Mat4_Basic<double>;
#endif

} // namespace libng::math