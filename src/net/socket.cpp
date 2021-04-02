#include <errno.h> //
#include <limits>  // std::numeric_limits

#include "dbg.hpp"
#include "net/socket.hpp"

namespace gnet {

#ifdef _WIN32
socket::startup_socket::startup_socket() {
  WSADATA data;
  if (int ret = WSAStartup(MAKEWORD(2, 2), &data); //
      ret != 0) {                                  //
    throw error_handler("[error] %s.\n", __GNET_PRETTY_FUNCTION__);
  }
}

socket::startup_socket::~startup_socket() {
  WSACleanup();
}
#endif

auto socket::startup_socket::init(void) -> void {
#ifdef _WIN32
  static startup_socket s_winsock;
#else
#endif
}

socket::~socket() {
  this->close();
}

auto socket::init_tcp(void) -> void {
  this->close();
  startup_socket::init();
  if (m_sockfd = ::socket(AF_INET, SOCK_STREAM, 0); //
      m_sockfd == INVALID_SOCKET) {                 //
    throw error_handler("[error] %s.\n", __GNET_PRETTY_FUNCTION__);
  }
}

auto socket::close(void) -> void {
  if (m_sockfd != INVALID_SOCKET) {
#ifdef _WIN32
    ::closesocket(m_sockfd);
#else
    ::close(m_sockfd);
#endif
  }
  m_sockfd = INVALID_SOCKET;
}

auto socket::bind(socket_addr const& addr) -> void {
  if (int const ret = ::bind(m_sockfd,     //
                             &addr,        //
                             addr.size()); //
      ret != 0) {
    throw error_handler("[error] %s.\n", __GNET_PRETTY_FUNCTION__);
  }
}

auto socket::connect(socket_addr const& addr) -> bool {
  if (!is_valid()) {
    return false;
  }

  if (int const ret = ::connect(m_sockfd, &addr, addr.size()); //
      ret < 0) {                                               //
    int const last_error_status = get_socket_error();
#ifdef _WIN32
    if (last_error_status == WSAEWOULDBLOCK) {
      return false;
    }
#else
    if (last_error_status == EINPROGRESS) {
      return false;
    }
#endif
    throw error_handler("[error] %s.\n", __GNET_PRETTY_FUNCTION__);
  }
  return true;
}

auto socket::listen(int const blacklog) -> void {
  if (int const ret = ::listen(m_sockfd, blacklog); //
      ret != 0) {                                   //
    throw error_handler("[error] %s\n", __GNET_PRETTY_FUNCTION__);
  }
}

auto socket::accept(socket& accepted_socket) -> bool {
  accepted_socket.close();
  auto const sockfd = ::accept(m_sockfd, nullptr, nullptr);
  if (sockfd == INVALID_SOCKET) {
    return false;
  }
  accepted_socket.m_sockfd = sockfd;
  return true;
}

auto socket::send(char const* const data,           //
                  size_t const data_size) -> void { //
  if (data_size > std::numeric_limits<uint32_t>::max() || data_size < 0) {
    throw error_handler("[error][%s] data size.\n", __GNET_PRETTY_FUNCTION__);
  }
  if (int const ret = ::send(m_sockfd,                    //
                             data,                        //
                             static_cast<int>(data_size), //
                             0);                          //
      ret < 0) {
    throw error_handler("[error][%s] send.\n", __GNET_PRETTY_FUNCTION__);
  }
}

auto socket::recv(std::vector<char>& buff,               //
                  size_t const recv_byte_size) -> void { //
  buff.clear();
  if (recv_byte_size > std::numeric_limits<int32_t>::max()) {
    throw error_handler("[error][%s] buff size.\n", __GNET_PRETTY_FUNCTION__);
  }
  buff.resize(recv_byte_size);
  recv(buff.data(), recv_byte_size);
}

auto socket::recv(char* buff,                            //
                  size_t const recv_byte_size) -> void { //
  if (recv_byte_size > std::numeric_limits<int32_t>::max()) {
    throw error_handler("[error][%s] buff size.\n", __GNET_PRETTY_FUNCTION__);
  }
  if (int const ret = ::recv(m_sockfd,                         //
                             buff,                             //
                             static_cast<int>(recv_byte_size), //
                             0);                               //
      ret < 0) {
    throw error_handler("[error][%s] recv.\n", __GNET_PRETTY_FUNCTION__);
  }
}

auto socket::fetch_available_buffer_size(void) -> size_t {
#ifdef _WIN32
  u_long sizes = 0;
  int ret      = ::ioctlsocket(m_sockfd, FIONREAD, &sizes);
#else
  int sizes = 0;
  int ret = ::ioctl(m_sockfd, FIONREAD, &sizes);
#endif
  if (ret != 0) {
    throw error_handler("[error] %s.\n", __GNET_PRETTY_FUNCTION__);
  }
  return static_cast<size_t>(sizes);
}

auto socket::set_nonblocking(bool is_enable) -> void {
#ifdef _WIN32
  u_long flag = is_enable ? 1 : 0;
  int ret     = ::ioctlsocket(m_sockfd, FIONBIO, &flag);
#else
  long flag = is_enable ? 1 : 0;
  int ret = ::ioctl(m_sockfd, FIONBIO, &flag);
#endif
  if (ret != 0) {
    throw error_handler("[error] %s.\n", __GNET_PRETTY_FUNCTION__);
  }
}

auto socket::get_fd(void) -> SOCKET {
  return m_sockfd;
}

auto socket::is_valid(void) -> bool {
  return m_sockfd != INVALID_SOCKET;
}

auto socket::get_socket_error(void) -> int {
#ifdef _WIN32
  int ret = ::WSAGetLastError();
#else
  int ret = errno;
#endif
  return ret;
}

} // namespace gnet
