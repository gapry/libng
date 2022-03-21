#include "net/socket_addr.hpp"

namespace libng {

socket_addr::socket_addr() {
  ::memset(&m_addr, 0, sizeof m_addr);
}

auto socket_addr::set_ipv4(uint8_t const a,           //
                           uint8_t const b,           //
                           uint8_t const c,           //
                           uint8_t const d) -> void { //
  m_addr.sa_family  = AF_INET;
  m_addr.sa_data[2] = a;
  m_addr.sa_data[3] = b;
  m_addr.sa_data[4] = c;
  m_addr.sa_data[5] = d;
}

auto socket_addr::set_port(uint16_t const port) -> void {
  *reinterpret_cast<uint16_t*>(m_addr.sa_data) = htons(port);
}

auto socket_addr::size(void) const -> addr_size_t {
  return m_length;
}

auto socket_addr::operator&(void) const -> addr_t const* {
  return &m_addr;
}

} // namespace libng
