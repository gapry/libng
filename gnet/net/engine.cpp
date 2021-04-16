#include "net/engine.hpp"

namespace gnet {

auto engine::listen(socket_addr const& addr, int backlog) -> void {
  auto& connection = m_listen_connection.emplace_back(new gnet::connection());
  try {
    connection->m_sock.init_tcp();
    connection->m_sock.set_nonblocking(true);
    connection->m_sock.bind(addr);
    connection->m_sock.listen(backlog);
    connection->m_status = connection::status::listening;
  } catch (...) {
    connection->close();
  }
}

auto engine::listen(gnet::string_view hostname, u16 port, int backlog) -> void {
}

auto engine::stop_listen(void) -> void {
}

auto engine::update(int timeout_ms) -> void {
}

auto engine::connect(socket_addr const& addr) -> gnet::connection* {
  throw;
}

auto engine::connect(gnet::string_view hostname, u16 port) -> gnet::connection* {
  throw;
}

auto engine::on_accept(gnet::connection* conn) -> void {
}

auto engine::on_connect(gnet::connection* conn) -> void {
}

auto engine::on_disconnect(gnet::connection* conn) -> void {
}

auto engine::on_recv(gnet::connection* conn) -> void {
}

auto engine::on_recv_pkt(gnet::connection* conn,             //
                         gnet::packet_header const& pkt_hdr, //
                         gnet::span<u8> data) -> void {      //
}

auto engine::send_stat(void) const -> engine::time_stat const& {
  return m_send_stat;
}

auto engine::recv_stat(void) const -> engine::time_stat const& {
  return m_recv_stat;
}

auto engine::time_stat::add(int cnt) -> void {
  m_last_second += cnt;
  m_last_second_count += cnt;
  m_total += cnt;
}

auto engine::time_stat::get_last_second(double delta_time) -> void {
  m_last_second       = static_cast<u64>(m_last_second_count / delta_time);
  m_last_second_count = 0;
}

} // namespace gnet