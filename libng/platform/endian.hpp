#pragma once

#include "platform/byte_order.hpp"
#include "platform/machine.hpp"

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

} // namespace libng
