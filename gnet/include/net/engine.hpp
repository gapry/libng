#pragma once

#include "config.hpp"
#include "noncopyable.hpp"

#include "platform/types.hpp"

#include "net/connection.hpp"
#include "net/io_mux.hpp"
#include "net/packet.hpp"
#include "net/packet_header.hpp"
#include "net/socket.hpp"
#include "net/socket_addr.hpp"

namespace gnet {

class engine : public noncopyable<engine> {
public:
  struct time_stat {
    u64 m_last_update       = 0;
    u64 m_last_second       = 0;
    u64 m_last_second_count = 0;
    u64 m_total             = 0;

    auto add(int cnt) -> void;

    auto get_last_second(double delta_time) -> void;
  };

  engine() = default;

  virtual ~engine() = default;

  auto listen(socket_addr const& addr, int backlog) -> void;

  auto listen(gnet::string_view, u16 port, int backlog) -> void;

  auto stop_listen(void) -> void;

  auto update(int timeout_ms) -> void;

  auto connect(gnet::socket_addr const& addr) -> gnet::connection*;

  auto connect(gnet::string_view hostname, u16 port) -> gnet::connection*;

  auto disconnect_all(void) -> void;

  auto listen_count(void) const -> size_t;

  auto connected_count(void) const -> size_t;

  auto send_stat(void) const -> time_stat const&;

  auto recv_stat(void) const -> time_stat const&;

  virtual auto on_accept(gnet::connection* conn) -> void;

  virtual auto on_connect(gnet::connection* conn) -> void;

  virtual auto on_disconnect(gnet::connection* conn) -> void;

  virtual auto on_error(gnet::connection* conn,              //
                        gnet::error_handler& error) -> void; //

  virtual auto on_recv(gnet::connection* conn) -> void;

  virtual auto on_recv_pkt(gnet::connection* conn,             //
                           gnet::packet_header const& pkt_hdr, //
                           gnet::span<u8> data) -> void;       //

  template<class packet>
  auto send_pkt(gnet::connection* conn, gnet::packet& pkt);

private:
  auto do_add_to_poll(gnet::vector<uptr<connection>>& poll_list) -> void;

  auto do_update_connection(gnet::connection* conn, poll_flags flag) -> void;

  auto do_accept(gnet::connection* conn);

  auto do_connect(gnet::connection* conn);

  auto do_disconnect(gnet::connection* conn);

  auto do_error(gnet::connection, gnet::error_handler const& error);

  auto do_add_recv_stat(gnet::connection* conn, int cnt);

  auto do_add_send_stat(gnet::connection* conn, int cnt);

  size_t m_max_pkt_size      = 1024;
  size_t m_max_pkt_per_frame = 60;

  gnet::vector<gnet::uptr<connection>> m_listen_connection;
  gnet::vector<gnet::uptr<connection>> m_sockets;

  gnet::vector<gnet::connection*> m_poll_sockets;
  gnet::vector<pollfd_t> m_pollfds;

  gnet::vector<u8> m_recv_pkt_buff;
  gnet::vector<u8> m_send_pkt_buff;

  time_stat m_send_stat;
  time_stat m_recv_stat;
};

} // namespace gnet
