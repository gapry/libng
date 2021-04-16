#include "dbg.hpp"
#include "log/log.hpp"
#include "net/engine.hpp"
#include "net/packet.hpp"

auto main(int, char**) -> int {
  GNET_LOG_INFO(__GNET_PRETTY_FUNCTION__);
  return 0;
}
