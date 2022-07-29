#include <libng_core/math/Vector/Vec3.hpp>

namespace libng::math {

#ifndef LIBNG_CPU_SSE
#error
#elif LIBNG_CPU_SSE
template Vec3_SSE<float>;
template Vec3_SSE<double>;
#else
template Vec3_Basic<float>;
template Vec3_Basic<double>;
#endif

} // namespace libng::math