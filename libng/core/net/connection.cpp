#include "net/connection.hpp"

namespace libng {

auto connection::close(void) -> void {
  m_status = status::none;
  m_sock.close();
}

auto connection::set_user_data(void* const data) -> void {
  m_user_data = data;
}

auto connection::get_user_data(void) -> void* {
  return m_user_data;
}

} // namespace libng