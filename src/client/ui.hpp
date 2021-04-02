#ifndef __GNET_UI_H__
#define __GNET_UI_H__

#include <cstdio>
#include <fmt/core.h>

#include "noncopyable.h"
#include "pch.h"

#include "client/game.h"
#include "client/player.h"

namespace gnet {

class ui : public gnet::noncopyable {
  char const* glsl_version = nullptr;
  SDL_Window* window       = nullptr;
  SDL_GLContext gl_context = nullptr;
  gnet::game* m_owner      = nullptr;
  bool m_is_executed       = true;
  ImVec4 clear_color       = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

public:
  ui(gnet::game* owner);

  ~ui();

  void on_update(void);

  void on_render(void);

  void execute(void);
};

} // namespace gnet

#endif
