#include <fmt/core.h>

#include "client/player.h"
#include "pch.h"

void gnet::player::movement(SDL_Event event) {
  auto logger = [](const char* const msg) {
    fmt::print("[log] key is {}\n", msg); //
  };

  switch (int key = event.key.keysym.scancode) {
    case SDL_SCANCODE_W: {
      set_offset_y(delta);
      logger("w");
    } break;
    case SDL_SCANCODE_S: {
      logger("s");
      set_offset_y(-delta);
    } break;
    case SDL_SCANCODE_A: {
      set_offset_x(-delta);
      logger("a");
    } break;
    case SDL_SCANCODE_D: {
      logger("d");
      set_offset_x(delta);
    } break;
    default: {
      logger("unknown");
    } break;
  }
}

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

void gnet::player::render(void) {
  glLoadIdentity();
  glTranslatef(-0.5f, -0.5f, 0.0f);
  glScalef(0.15f, 0.15f, 0.0f);
  glBegin(GL_TRIANGLES);
  {
    // clang-format off
    glColor4f(1, 0, 0, 0); glVertex3f(0   + get_offset_x(), 1 + get_offset_y(), 0); // point#1 (R)
    glColor4f(0, 1, 0, 0); glVertex3f(0.5 + get_offset_x(), 2 + get_offset_y(), 0); // point#2 (G)
    glColor4f(0, 0, 1, 0); glVertex3f(1   + get_offset_x(), 1 + get_offset_y(), 0); // point#3 (B)
    // clang-format on
  }
  glEnd();
}
