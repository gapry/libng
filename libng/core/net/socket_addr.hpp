#pragma once

#include "dbg.hpp"
#include "error_handler.hpp"
#include "noncopyable.hpp"
#include "pch.hpp"

namespace libng {

class socket_addr : public noncopyable<socket_addr> {
  using addr_t      = struct sockaddr;
  using addr_size_t = socklen_t;

  addr_t m_addr;
  addr_size_t m_length = sizeof m_addr;

public:
  socket_addr();

  ~socket_addr() = default;

  auto set_port(uint16_t const port) -> void;

  auto set_ipv4(uint8_t const a,          //
                uint8_t const b,          //
                uint8_t const c,          //
                uint8_t const d) -> void; //

  auto size(void) const -> addr_size_t;

  auto operator&(void) const -> addr_t const*;
};

} // namespace libng
