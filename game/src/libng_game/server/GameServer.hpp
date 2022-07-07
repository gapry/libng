#pragma once

namespace libng {

class GameServer {
public:
  void onAccept();

  void onConnect();

  void onDisconnect();

  void onRecvPacket();
};

} // namespace libng
