#ifndef __GNET_RENDER_H__
#define __GNET_RENDER_H__

#include "client/player.h"
#include "noncopyable.h"
#include "pch.h"

namespace gnet {

class game : public gnet::noncopyable {
public:
  game();

  virtual ~game();

  void execute(void);

  virtual void on_update(float delta_time);

  virtual void on_event(SDL_Event& event);
};

} // namespace gnet

#endif
