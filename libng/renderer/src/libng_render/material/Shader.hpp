#pragma once

#include <libng_core/libcxx/string.hpp>
#include <libng_core/types/RefCountBase.hpp>

namespace libng {

class Shader : public RefCountBase {
public:
  static void Find(const String& ShaderName);
};

} // namespace libng