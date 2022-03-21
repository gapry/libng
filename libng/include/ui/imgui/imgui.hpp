#pragma once

#include <cstdio>
#include <fmt/core.h>

#include "noncopyable.hpp"
#include "pch.hpp"

#include "ui/config.hpp"

#include "client/game.hpp"
#include "client/player.hpp"

namespace libng {

class ui : public libng::noncopyable<ui> {
  char const* glsl_version = nullptr;
  SDL_Window* window       = nullptr;
  SDL_GLContext gl_context = nullptr;
  libng::game* m_owner     = nullptr;
  bool m_is_executed       = true;
  ImVec4 clear_color       = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

public:
  ui(libng::game* owner);

  ~ui();

  auto on_update(void) -> void;

  auto on_render(void) -> void;

  auto execute(void) -> void;
};

} // namespace libng
