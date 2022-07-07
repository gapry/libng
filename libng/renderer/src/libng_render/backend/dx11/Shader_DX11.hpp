#pragma once

#include <libng_render/material/Shader.hpp>

namespace libng {

class Shader_DX11 : public Shader {
public:
  Shader_DX11(StrView filename);
};

} // namespace libng