#pragma once

#include "platform/compiler.hpp"
#include "platform/type.hpp"

namespace gnet {

class byte_order {
public:
  class identity {
  public:
    constexpr static u16 get(u16 value) {
      return value;
    }

    constexpr static u32 get(u32 value) {
      return value;
    }

    constexpr static i16 get(i16 value) {
      return value;
    }

    constexpr static i32 get(i32 value) {
      return value;
    }

    constexpr static f32 get(f32 value) {
      return value;
    }
  };

  class inverse {
  public:
    constexpr static u16 get(u16 value) {
      return static_cast<u16>((value >> 8) | (value << 8));
    }

    constexpr static u32 get(u32 value) {
      value = ((value << 8) & 0xFF00FF00UL) | ((value >> 8) & 0x00FF00FFUL);
      return (value >> 16) | (value << 16);
    }

    constexpr static i16 get(i16 value) {
      return static_cast<i16>(get(static_cast<u16>(value)));
    }

    constexpr static i32 get(i32 value) {
      return static_cast<i32>(get(static_cast<u32>(value)));
    }

    GNET_INLINE static f32 get(f32 value) {
      u32 _value = get(*reinterpret_cast<u32 const*>(&value));
      return *reinterpret_cast<f32 const*>(&_value);
    }
  };
};

} // namespace gnet
