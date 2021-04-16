#pragma once

#include "dbg.hpp"
#include "error_handler.hpp"
#include "noncopyable.hpp"
#include "packet_header.hpp"
#include "platform/byte_order.hpp"
#include "platform/endian.hpp"
#include "platform/types.hpp"
#include "serialization/deserializer.hpp"
#include "serialization/serializer.hpp"

namespace gnet {

class packet_header;

class packet : public gnet::noncopyable<packet> {
  packet_header m_header;

public:
  explicit packet(packet_header const& cmd)
    : m_header(cmd) {
  }

  auto write_to_buffer(gnet::vector<u8>& buff) -> void;

  auto read_from_buffer(gnet::span<u8 const> buff) -> void;

  virtual auto on_write(serializer& writer) -> void = 0;

  virtual auto on_read(deserializer& reader) -> void = 0;
};

} // namespace gnet
