#ifndef __GNET_UI_H__
#define __GNET_UI_H__

#include <cstdio>
#include <fmt/core.h>

#include "client/player.h"
#include "pch.h"

namespace gnet {

class ui {
  SDL_GLContext gl_context;
  char* glsl_version;
  SDL_Window* window;

public:
  ui(ImGuiIO& io,                                              //
     SDL_Window* window,                                       //
     gnet::player& player,                                     //
     void (*game_loop)(SDL_Window*, ImGuiIO&, gnet::player&)); //

  ~ui();

private:
  void init_imgui(ImGuiIO& io);

  int init_opengl_loader(void);

  int init_sdl(void);
};

} // namespace gnet

#endif
