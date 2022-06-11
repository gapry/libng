#pragma once

#include <libng_core/libcxx/string.hpp>

namespace libng {

class Shader {
public:
  static void Find(const String& ShaderName);
};

} // namespace libng