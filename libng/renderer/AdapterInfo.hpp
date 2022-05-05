#pragma once

#include <types/number.hpp>
#include <libcxx/util.hpp>

namespace libng {

struct AdapterInfo {
  String adapterName;
  i64 memorySize = 0;

  bool multithread       = false;
  bool hasComputeShader  = false;
  bool shaderHasFloat64  = false;
  int minThreadGroupSize = 1;
};

} // namespace libng