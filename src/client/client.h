#ifndef __GNET_CLIENT_H__
#define __GNET_CLIENT_H__

#include "client/game.h"

namespace gnet {

class client : public gnet::game {
public:
  virtual void on_update(float delta_time) override final;

  virtual void on_event(SDL_Event& event) override final;
};

} // namespace gnet

#endif
