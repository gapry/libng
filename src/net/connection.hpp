#pragma once

#include "net/packet.hpp"
#include "net/socket.hpp"
#include "noncopyable.hpp"
#include "platform/type.hpp"

namespace gnet {

class engine;

class connection : public noncopyable<connection> {
  enum class status {
    none,
    listening,
    connecting,
    connected,
  };

  friend class engine;

public:
  connection() = default;

  ~connection() = default;

protected:
  socket m_sock;
  status m_status         = status::none;
  u64 m_totoal_send_bytes = 0;
  u64 m_totoal_recv_bytes = 0;
}

} // namespace gnet
