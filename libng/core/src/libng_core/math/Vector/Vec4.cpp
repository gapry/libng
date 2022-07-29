#include <libng_core/math/Vector/Vec4.hpp>
#include <libng_core/platform/sse.hpp>

namespace libng::math {

#ifndef LIBNG_CPU_SSE
#error
#elif LIBNG_CPU_SSE
template Vec4_SSE<float>;
template Vec4_SSE<double>;
#else
template Vec4_Basic<float>;
template Vec4_Basic<double>;
#endif

} // namespace libng::math