#ifndef __GNET_GAME_H__
#define __GNET_GAME_H__

#include "client/player.h"
#include "noncopyable.h"
#include "pch.h"

namespace gnet {

class game : public gnet::noncopyable {
  ImVec2 m_dir  = ImVec2(0, 0);
  float m_speed = 200.0f;

protected:
  bool get_input_key(SDL_Keycode key);

public:
  game();

  virtual ~game();

  void execute(void);

  virtual void on_update(float delta_time);

  virtual void on_event(SDL_Event& event);

  float get_speed(void) const {
    return m_speed;
  }

  void set_dir_x(int k) {
    m_dir.x += k;
  }

  void set_dir_y(int k) {
    m_dir.y += k;
  }

  auto get_dir_x(void) const {
    return m_dir.x;
  }

  auto get_dir_y(void) const {
    return m_dir.y;
  }
};

} // namespace gnet

#endif
