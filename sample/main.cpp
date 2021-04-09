#include "app_client.hpp"
#include "app_server.hpp"

auto main(int, char**) -> int {
  gnet::app_client app;
  app.execute();
  return 0;
}
