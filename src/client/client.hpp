#ifndef __GNET_CLIENT_H__
#define __GNET_CLIENT_H__

#include "client/game.h"
#include "client/player.h"

namespace gnet {

class client : public gnet::game {
  gnet::player player = gnet::player(400.0f, 300.0f);

public:
  virtual void on_update(float delta_time) override final;

  virtual void on_event(SDL_Event& event) override final;
};

} // namespace gnet

#endif
