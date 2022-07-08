#pragma once

#include <libng_render/RendererCommon.hpp>

namespace libng {

class Shader : public RefCountBase {
public:
  static void Find(const String& ShaderName);
};

} // namespace libng