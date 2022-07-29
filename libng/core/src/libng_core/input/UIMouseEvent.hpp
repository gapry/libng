#pragma once

#include <libng_core/input/UIEventModifier.hpp>
#include <libng_core/input/UIMouseEventButton.hpp>
#include <libng_core/input/UIMouseEventType.hpp>
#include <libng_core/math/Vector/Vec2.hpp>
#include <libng_core/types/enum.hpp>

// clang-format off

namespace libng {
  using Type     = UIMouseEventType;
  using Modifier = UIEventModifier;
  using Button   = UIMouseEventButton;

  bool isUp()       const { return type == Type::Up;     }
  bool isDown()     const { return type == Type::Down;   }
  bool isMove()     const { return type == Type::Move;   }
  bool isScroll()   const { return type == Type::Scroll; }
  bool isDragging() const { return type == Type::Move && pressedButtons != Button::None; }

  Type     type           = Type::None;
  Modifier modifier       = Modifier::None;
  Button   button         = Button::None;
  Button   pressedButtons = Button::None;

  Vec2f pos{0, 0};
  Vec2f deltaPos{0, 0};
  Vec2f scroll{0, 0};
} // namespace libng