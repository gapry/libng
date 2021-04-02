#pragma once

#include "gui.hpp"
#include "noncopyable.hpp"
#include "pch.hpp"

namespace gnet {

class player : public gnet::noncopyable<player> {
  float x = 0.0f;
  float y = 0.0f;

public:
  explicit player(float x, float y)
    : x(x)
    , y(y) {
  }

  ~player() = default;

  auto get_x(void) const -> float;

  auto get_y(void) const -> float;

  auto set_x(float k) -> void;

  auto set_y(float k) -> void;
};

} // namespace gnet
