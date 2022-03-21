#include "client/player.hpp"

float libng::player::get_x(void) const {
  return x;
}

float libng::player::get_y(void) const {
  return y;
}

void libng::player::set_x(float new_x) {
  x = new_x;
}

void libng::player::set_y(float new_y) {
  y = new_y;
}
