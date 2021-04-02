#pragma once

#include "guptr.hpp"
#include "gvector.hpp"
#include "net/connection.hpp"
#include "net/io_mux.hpp"
#include "noncopyable.hpp"
#include "platform/type.hpp"

namespace gnet {

class engine : public noncopyable<engine> {
  gnet::vector<gnet::uptr<connection>> m_listen_connection;
  gnet::vector<gnet::uptr<connection>> m_connections;

  gnet::vector<u8> m_recv_pkt_buff;
  gnet::vector<u8> m_send_pkt_buff;

public:
  engine() = default;

  virtual ~engine() = default;

  virtual auto on_accept(connection* conn) -> void;

  virtual auto on_connect(connection* conn) -> void;

  virtual auto on_disconnect(connection* conn) -> void;
};

} // namespace gnet
