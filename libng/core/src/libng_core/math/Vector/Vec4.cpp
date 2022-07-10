#include <libng_core/math/Vector/Vec4.hpp>
#include <libng_core/platform/sse.hpp>

namespace libng::math {

#if LIBNG_MATH_USE_SSE
// template Vec4_SSE<float>;
// template Vec4_SSE<double>;
#else
template Vec4_Basic<float>;
template Vec4_Basic<double>;
#endif

} // namespace libng::math