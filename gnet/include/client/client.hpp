#pragma once

#include "client/game.hpp"
#include "client/player.hpp"

namespace gnet {

class client : public gnet::game {
  gnet::player player = gnet::player(400.0f, 300.0f);

public:
  virtual auto on_update(float delta_time) -> void override final;

  virtual auto on_event(SDL_Event& event) -> void override final;
};

} // namespace gnet
