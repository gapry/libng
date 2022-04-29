#pragma once

#include <types/number.hpp>

namespace libng {

// clang-format off
enum class RenderDataType: u8 {
	None,
  //
	Int8,		 Int8x2,	  Int8x3,    Int8x4,
	Int16,	 Int16x2,	  Int16x3,   Int16x4,
	Int32,	 Int32x2,	  Int32x3,   Int32x4,
	Int64,	 Int64x2,	  Int64x3,   Int64x4,
  //
	UInt8,	 UInt8x2,	  UInt8x3,	 UInt8x4,
	UInt16,	 UInt16x2,	UInt16x3,	 UInt16x4,
	UInt32,	 UInt32x2,	UInt32x3,	 UInt32x4,
	UInt64,	 UInt64x2,	UInt64x3,	 UInt64x4,
  //
	Float16, Float16x2,	Float16x3, Float16x4,
	Float32, Float32x2,	Float32x3, Float32x4,
	Float64, Float64x2,	Float64x3, Float64x4,
  //
	UNorm8,  UNorm8x2,	UNorm8x3,  UNorm8x4,
};

}