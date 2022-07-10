#pragma once

#include <libng_core/math/Color/Color.hpp>
#include <libng_core/math/Tuple/Tuple2.hpp>
#include <libng_core/math/Tuple/Tuple3.hpp>
#include <libng_core/math/Tuple/Tuple4.hpp>

#include <libng_render/type/RenderDataType.hpp>

// clang-format off
namespace libng {

struct RenderDataTypeUtil {
  using Type = RenderDataType;

  template<class T> static constexpr Type get();

	template<> static constexpr Type get<void>() { return Type::None;  }

	template<> static constexpr Type get<i8 >() { return Type::Int8;  }
	template<> static constexpr Type get<i16>() { return Type::Int16; }
	template<> static constexpr Type get<i32>() { return Type::Int32; }
	template<> static constexpr Type get<i64>() { return Type::Int64; }

	template<> static constexpr Type get<u8 >() { return Type::UInt8;  }
	template<> static constexpr Type get<u16>() { return Type::UInt16; }
	template<> static constexpr Type get<u32>() { return Type::UInt32; }
	template<> static constexpr Type get<u64>() { return Type::UInt64; }

	template<> static constexpr Type get<f32>() { return Type::Float32; }
	template<> static constexpr Type get<f64>() { return Type::Float64; }

	template<> static constexpr Type get<math::Tuple2f>() { return Type::Float32x2; }
	template<> static constexpr Type get<math::Tuple2d>() { return Type::Float64x2; }

	template<> static constexpr Type get<math::Tuple3f>() { return Type::Float32x3; }
	template<> static constexpr Type get<math::Tuple3d>() { return Type::Float64x3; }

	template<> static constexpr Type get<math::Tuple4f>() { return Type::Float32x4; }
	template<> static constexpr Type get<math::Tuple4d>() { return Type::Float64x4; }

	template<> static constexpr Type get<math::Color4b>() { return Type::UNorm8x4; }
};

} // namespace libng