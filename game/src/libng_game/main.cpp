#include <libng_game/client/GameClient.hpp>

int main() {
  libng::GameClient client;
  libng::GameClient::CreateDesc desc;
  client.run(desc);
  return 0;
}
