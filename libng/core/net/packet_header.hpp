#pragma once

#include "platform/types.hpp"
#include "serialization/serializer.hpp"

namespace libng {

using pkt_cmd_t    = u32;
using pkt_length_t = u16;

class packet_header {
public:
  packet_header() = default;

  packet_header(pkt_cmd_t const& cmd)
    : m_cmd(cmd) {
  }

  ~packet_header() = default;

  template<class S>
  auto write(S& writer) {
    // writer.write_fixed(m_length);
    // writer.write(m_cmd);
  }

  pkt_cmd_t m_cmd       = 0;
  pkt_length_t m_length = 0;
};

} // namespace libng
