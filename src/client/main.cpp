#include "client/ui.h"

int main(int, char**) {
  ImGuiIO io;
  SDL_Window* window;
  gnet::player player(0.0f, 0.0f);
  gnet::ui(io, window, player, gnet::render::game_loop);
  return 0;
}
