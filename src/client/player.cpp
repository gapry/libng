#include <fmt/core.h>

#include "client/player.h"
#include "pch.h"

float gnet::player::get_offset_x(void) const {
  return offset_x;
}

float gnet::player::get_offset_y(void) const {
  return offset_y;
}

void gnet::player::set_offset_x(float k) {
  offset_x = offset_x + k;
}

void gnet::player::set_offset_y(float k) {
  offset_y = offset_y + k;
}
