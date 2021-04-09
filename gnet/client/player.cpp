#include "client/player.hpp"

float gnet::player::get_x(void) const {
  return x;
}

float gnet::player::get_y(void) const {
  return y;
}

void gnet::player::set_x(float new_x) {
  x = new_x;
}

void gnet::player::set_y(float new_y) {
  y = new_y;
}
