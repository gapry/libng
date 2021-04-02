#include "client/client.hpp"

int main(int, char**) {
  gnet::client app;
  app.execute();
  return 0;
}
