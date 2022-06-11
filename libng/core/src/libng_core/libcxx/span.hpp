#pragma once

#include <libng_core/types/function.hpp>
#include <libng_core/types/number.hpp>
#include <third_party/eastl/eastl.hpp>

namespace libng::libcxx {

template<typename T>
class span {
public:
};

using byte_span = span<const u8>;

} // namespace libng::libcxx

namespace libng {

template<class T>
using Span = eastl::span<T>;

using ByteSpan = Span<const u8>;

template<class DST, class SRC>
LIBNG_INLINE Span<DST> spanCast(Span<SRC> src) {
  size_t sizeInBytes = src.size() * sizeof(SRC);
  return Span<DST>(reinterpret_cast<DST*>(src.data()), sizeInBytes / sizeof(DST));
}

} // namespace libng