#ifndef __GNET_SOCKET_H__
#define __GNET_SOCKET_H__

#include "noncopyable.h"
#include "pch.h"

namespace gnet {

class socket : public gnet::noncopyable {
public:
#ifdef _WIN32
  using int socklen_t = int;
#else
  using SOCKET                = int;
  const SOCKET INVALID_SOCKET = -1;
#endif

private:
  SOCKET m_sock = INVALID_SOCKET;
}

} // namespace gnet

#endif
