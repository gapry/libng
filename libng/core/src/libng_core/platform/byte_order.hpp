#pragma once

#include <libng_core/platform/compiler.hpp>
#include <libng_core/types/number.hpp>
#include <libng_core/types/function.hpp>

namespace libng {

class byte_order {
public:
  class identity {
  public:
    // clang-format off
    constexpr static u8  get(u8  value) { return value; }
    constexpr static u16 get(u16 value) { return value; }
    constexpr static u32 get(u32 value) { return value; }
    constexpr static u64 get(u64 value) { return value; }

    constexpr static i8  get(i8  value) { return value; }
    constexpr static i16 get(i16 value) { return value; }
    constexpr static i32 get(i32 value) { return value; }
    constexpr static i64 get(i64 value) { return value; }

    constexpr static f32 get(f32 value) { return value; }
    constexpr static f64 get(f64 value) { return value; }
    // clang-format on
  };

  class inverse {
  public:
    // clang-format off
    constexpr static i8  get(i8  value) { return static_cast<i8 >(get(static_cast<u8 >(value))); }
    constexpr static i16 get(i16 value) { return static_cast<i16>(get(static_cast<u16>(value))); }
    constexpr static i32 get(i32 value) { return static_cast<i32>(get(static_cast<u32>(value))); }
    constexpr static i64 get(i64 value) { return static_cast<i64>(get(static_cast<u64>(value))); }
    // clang-format on

    constexpr static u8 get(u8 value) {
      return value;
    }

    constexpr static u16 get(u16 value) {
      return static_cast<u16>((value >> 8) | (value << 8));
    }

    constexpr static u32 get(u32 value) {
      value = ((value << 8) & 0xFF00FF00UL) | ((value >> 8) & 0x00FF00FFUL);
      return (value >> 16) | (value << 16);
    }

    constexpr static u64 get(u64 value) {
      value = ((value << 8) & 0xFF00FF00FF00FF00ULL) | ((value >> 8) & 0x00FF00FF00FF00FFULL);
      value = ((value << 16) & 0xFFFF0000FFFF0000ULL) | ((value >> 16) & 0x0000FFFF0000FFFFULL);
      return (value >> 32) | (value << 32);
    }

    LIBNG_INLINE static f32 get(f32 value) {
      u32 cache = get(*reinterpret_cast<u32 const*>(&value));
      return *reinterpret_cast<f32 const*>(&cache);
    }

    LIBNG_INLINE static f64 get(f64 value) {
      u64 cache = get(*reinterpret_cast<u64 const*>(&value));
      return *reinterpret_cast<f64 const*>(&cache);
    }
  };
};

} // namespace libng
