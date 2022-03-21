#pragma once

#include "noncopyable.hpp"
#include "pch.hpp"

#include "client/config.hpp"
#include "ui/imgui/imgui.hpp"

namespace libng {

class player : public libng::noncopyable<player> {
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

} // namespace libng
