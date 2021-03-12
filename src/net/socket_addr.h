#ifndef __GNET_SOCKET_ADDR_H__
#define __GNET_SOCKET_ADDR_H__

#include "noncopyable.h"
#include "pch.h"

namespace gnet {

class socket_addr : public gnet::noncopyable {
  using addr_t = struct sockaddr;

public:
  void set_port(uint16_t port);

  uint16_t get_port(void) const;

  void set_ipv4(uint8_t part1, uint8_t part2, uint8_t part3, uint8_t part4);

  void set_ipv4(const char* const hostname, const char* const service = nullptr);

private:
  addr_t m_addr;
}

} // namespace gnet

#endif
