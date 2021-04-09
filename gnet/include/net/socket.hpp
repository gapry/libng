#pragma once

#include "config.hpp"
#include "error_handler.hpp"
#include "noncopyable.hpp"
#include "pch.hpp"

#include "net/socket_addr.hpp"
#include "platform/os.hpp"

namespace gnet {

class socket : public noncopyable<socket> {
  struct startup_socket {
  public:
#ifdef GNET_OS_WINDOWS
    startup_socket();

    ~startup_socket();
#endif
    static void init(void);
  };

#ifdef GNET_OS_WINDOWS
  using socklen_t = int;
#else
  using SOCKET = int;

  static constexpr SOCKET INVALID_SOCKET = -1;
#endif

  static constexpr int default_backlog = 32;
  SOCKET m_sockfd                      = INVALID_SOCKET;

public:
  socket() = default;

  ~socket();

  auto init_tcp(void) -> void;

  auto close(void) -> void;

  auto bind(const socket_addr& bind_socket) -> void;

  auto listen(int const backlog = default_backlog) -> void;

  auto accept(socket& accepted_socket) -> bool;

  auto connect(socket_addr const& addr) -> bool;

  auto sendto(socket_addr const& addr,         //
              char const* const data) -> void; //

  auto send(char const* const data,          //
            size_t const data_size) -> void; //

  template <size_t N>
  auto send(char const (&data)[N]) -> void {
    if (N) {
      send(data, N - 1);
    }
  }

  auto recvfrom(socket_addr& addr,                    //
                gnet::vector<char>& buff,             //
                size_t const recv_byte_size) -> void; //

  auto recv(gnet::vector<char>& buff,             //
            size_t const recv_byte_size) -> void; //

  auto recv(char* buff,                           //
            size_t const recv_byte_size) -> void; //

  auto fetch_available_buffer_size(void) -> size_t;

  auto set_nonblocking(bool is_enable) -> void;

  auto get_socket_error(void) -> int;

  auto get_fd(void) -> SOCKET;

  auto is_valid(void) -> bool;
};

} // namespace gnet
