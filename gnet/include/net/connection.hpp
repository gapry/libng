#pragma once

#include "net/packet.hpp"
#include "net/socket.hpp"
#include "noncopyable.hpp"
#include "platform/types.hpp"

namespace gnet {

class engine;

class connection : public noncopyable<connection> {
  friend class engine;

public:
  enum class status {
    none,
    listening,
    connecting,
    connected,
  };

  connection() = default;

  ~connection() = default;

  auto set_user_data(void* const data) -> void;

  auto get_user_data(void) -> void*;

  auto close(void) -> void;

protected:
  socket m_sock;
  status m_status         = status::none;
  void* m_user_data       = nullptr;
  u64 m_totoal_send_bytes = 0;
  u64 m_totoal_recv_bytes = 0;
};

} // namespace gnet
