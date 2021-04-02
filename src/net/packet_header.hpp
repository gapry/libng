#pragma once

#include "net/packet.hpp"

namespace gapry {

class packet_header {
  pkt_cmd_t m_cmd       = 0;
  pkt_length_t m_length = 0;

public:
  packet_header() = default;

  packet_header(pkt_cmd_t const& cmd)
    : m_cmd(cmd) {
  }

  ~packet_header() = default;
};

} // namespace gapry
