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

namespace libng {

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

  auto listen(libng::string_view, u16 port, int backlog) -> void;

  auto stop_listen(void) -> void;

  auto update(int timeout_ms) -> void;

  auto connect(libng::socket_addr const& addr) -> libng::connection*;

  auto connect(libng::string_view hostname, u16 port) -> libng::connection*;

  auto disconnect_all(void) -> void;

  auto listen_count(void) const -> size_t;

  auto connected_count(void) const -> size_t;

  auto send_stat(void) const -> time_stat const&;

  auto recv_stat(void) const -> time_stat const&;

  virtual auto on_accept(libng::connection* conn) -> void;

  virtual auto on_connect(libng::connection* conn) -> void;

  virtual auto on_disconnect(libng::connection* conn) -> void;

  virtual auto on_error(libng::connection* conn,              //
                        libng::error_handler& error) -> void; //

  virtual auto on_recv(libng::connection* conn) -> void;

  virtual auto on_recv_pkt(libng::connection* conn,             //
                           libng::packet_header const& pkt_hdr, //
                           libng::span<u8> data) -> void;       //

  template<class packet>
  auto send_pkt(libng::connection* conn, libng::packet& pkt);

private:
  auto do_add_to_poll(libng::vector<uptr<connection>>& poll_list) -> void;

  auto do_update_connection(libng::connection* conn, poll_flags flag) -> void;

  auto do_accept(libng::connection* conn);

  auto do_connect(libng::connection* conn);

  auto do_disconnect(libng::connection* conn);

  auto do_error(libng::connection, libng::error_handler const& error);

  auto do_add_recv_stat(libng::connection* conn, int cnt);

  auto do_add_send_stat(libng::connection* conn, int cnt);

  size_t m_max_pkt_size      = 1024;
  size_t m_max_pkt_per_frame = 60;

  libng::vector<libng::uptr<connection>> m_listen_connection;
  libng::vector<libng::uptr<connection>> m_sockets;

  libng::vector<libng::connection*> m_poll_sockets;
  libng::vector<pollfd_t> m_pollfds;

  libng::vector<u8> m_recv_pkt_buff;
  libng::vector<u8> m_send_pkt_buff;

  time_stat m_send_stat;
  time_stat m_recv_stat;
};

} // namespace libng
