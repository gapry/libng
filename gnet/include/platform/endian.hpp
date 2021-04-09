#pragma once

#include "platform/byte_order.hpp"
#include "platform/machine.hpp"

class little_endian {
public:
#if GNET_ENDIAN_LITTLE
  using to_host   = byte_order::identity;
  using from_host = byte_order::identity;
#elif GNET_ENDIAN_BIG
  using to_host   = byte_order::inverse;
  using from_host = byte_order::inverse;
#endif
};

class big_endian {
public:
#if GNET_ENDIAN_LITTLE
  using to_host   = byte_order::inverse;
  using from_host = byte_order::inverse;
#elif GNET_ENDIAN_BIG
  using to_host   = byte_order::identity;
  using from_host = byte_order::identity;
#endif
};
