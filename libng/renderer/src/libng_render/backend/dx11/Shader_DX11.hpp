#pragma once

#include <libng_render/material/Shader.hpp>

namespace libng {

class Shader_DX11 : public Shader {
  using Base = Shader;

public:
  Shader_DX11(StrView filename);
};

} // namespace libng