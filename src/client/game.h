#ifndef __GNET_RENDER_H__
#define __GNET_RENDER_H__

#include "client/player.h"
#include "noncopyable.h"
#include "pch.h"

namespace gnet {

class render : public gnet::noncopyable {
public:
  static void game_loop(SDL_Window* window, ImGuiIO& io, gnet::player& player);
};

} // namespace gnet

#endif