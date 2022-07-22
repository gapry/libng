#pragma once

#include <libng_core/platform/byte_order.hpp>
#include <libng_core/platform/machine.hpp>

namespace libng {

class little_endian {
public:
#if LIBNG_ENDIAN_LITTLE
  using to_host   = byte_order::identity;
  using from_host = byte_order::identity;
#elif LIBNG_ENDIAN_BIG
  using to_host   = byte_order::inverse;
  using from_host = byte_order::inverse;
#endif
};

class big_endian {
public:
#if LIBNG_ENDIAN_LITTLE
  using to_host   = byte_order::inverse;
  using from_host = byte_order::inverse;
#elif LIBNG_ENDIAN_BIG
  using to_host   = byte_order::identity;
  using from_host = byte_order::identity;
#endif
};

#if LIBNG_ENDIAN_LITTLE
constexpr char32_t FourCC(char a, char b, char c, char d) {
  return static_cast<char32_t>(a) | static_cast<char32_t>(b) << 8 | static_cast<char32_t>(c) << 16 |
         static_cast<char32_t>(d) << 24;
}
#elif LIBNG_ENDIAN_BIG
constexpr char32_t FourCC(char a, char b, char c, char d) {
  return static_cast<char32_t>(a) >> 24 | static_cast<char32_t>(b) << 16 | static_cast<char32_t>(c) << 8 |
         static_cast<char32_t>(d);
}
#else
#error "Unknown Host Endian"
#endif

constexpr char32_t FourCC(const char (&sz)[5]) {
  return FourCC(sz[0], sz[1], sz[2], sz[3]);
}

} // namespace libng
