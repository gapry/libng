#pragma once

#include <libng_core/libcxx/span.hpp>
#include <libng_core/libcxx/string_view.hpp>

namespace libng {

LIBNG_INLINE ByteSpan ByteSpan_make(StrView v) {
  return ByteSpan(reinterpret_cast<const u8*>(v.data()), v.size());
}

LIBNG_INLINE StrView StrView_make(ByteSpan s) {
  return StrView(reinterpret_cast<const char*>(s.data()), s.size());
}

} // namespace libng
