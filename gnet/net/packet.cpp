#include "net/packet.hpp"

namespace gnet {

auto packet::write_to_buffer(gnet::vector<u8>& buff) -> void { //
  buff.clear();
  serializer writer(buff);
  writer.write(m_header);
  on_write(writer);
  auto pkt_size                                 = static_cast<pkt_length_t>(buff.size());
  *reinterpret_cast<pkt_length_t*>(buff.data()) = little_endian::from_host::get(pkt_size);
}

auto packet::read_from_buffer(gnet::span<u8 const> buff) -> void {
  deserializer reader(buff);
  auto cmd = m_header.m_cmd;
  reader.read(m_header);
  on_read(reader);
  if (cmd != m_header.m_cmd) {
    m_header.m_cmd = cmd;
    throw;
  }
}

} // namespace gnet