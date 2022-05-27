#pragma once

#include <types/number.hpp>

namespace libng {

enum class VertexType : u64
{
  None
  // posType			  : 8 bit // Issue: Type and Count
  // colorType		  : 8 bit
  // colorCount		  : 2 bit
  // uvType			    : 8 bit
  // uvCount			  : 8 bit
  // normalType		  : 8 bit
  // normalCount		: 2 bit
  // tangentCount		: 2 bit // Issue: Type and Count
  // binormalCount	: 2 bit // Issue: Type and Count
};

} // namespace libng