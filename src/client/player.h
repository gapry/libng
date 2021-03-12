#ifndef __GNET_CLIENT_H__
#define __GNET_CLIENT_H__

#include "pch.h"

namespace gnet {

class player {
  float offset_x = 0.0f;
  float offset_y = 0.0f;
  float delta    = 0.15f;

public:
  explicit player(float x, float y)
    : offset_x{x}
    , offset_y{y} {
  }

  ~player() = default;

  void movement(SDL_Event event);

  float get_offset_x(void) const;

  float get_offset_y(void) const;

  void set_offset_x(float k);

  void set_offset_y(float k);

  void render(void);
};

} // namespace gnet

#endif
