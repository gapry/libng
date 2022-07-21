#pragma once

#include <libng_render/RendererCommon.hpp>
#include <libng_render/material/ShaderPass.hpp>

namespace libng {

class Shader : public RefCountBase {
public:
  static void Find(const String& ShaderName);

private:
  Vector_<UPtr<ShaderPass>, 2> _passes;
};

} // namespace libng