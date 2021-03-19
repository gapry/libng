#include "client/client.h"

int main(int, char**) {
  gnet::client app;
  app.execute();
  return 0;
}
