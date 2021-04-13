#pragma once

#include "noncopyable.hpp"
#include "pch.hpp"

#include "client/config.hpp"
#include "client/player.hpp"
#include "ui/imgui/imgui.hpp"

namespace gnet {

class game : public gnet::noncopyable<game> {
  ImVec2 m_dir  = ImVec2(0, 0);
  float m_speed = 200.0f;

protected:
  auto get_input_key(SDL_Keycode key) -> bool;

public:
  game();

  virtual ~game();

  void execute(void);

  virtual auto on_update(float delta_time) -> void;

  virtual auto on_event(SDL_Event& event) -> void;

  auto get_speed(void) const {
    return m_speed;
  }

  auto set_dir_x(int k) {
    m_dir.x += k;
  }

  auto set_dir_y(int k) {
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
