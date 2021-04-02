#ifndef __GNET_PLAYER_H__
#define __GNET_PLAYER_H__

#include "noncopyable.h"
#include "pch.h"

namespace gnet {

class player : public gnet::noncopyable {
  float x = 0.0f;
  float y = 0.0f;

public:
  explicit player(float x, float y)
    : x(x)
    , y(y) {
  }

  ~player() = default;

  float get_x(void) const;

  float get_y(void) const;

  void set_x(float k);

  void set_y(float k);
};

} // namespace gnet

#endif
