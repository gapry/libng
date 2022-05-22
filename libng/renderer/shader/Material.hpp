#pragma once

#include <renderer/shader/Shader.hpp>
#include <renderer/shader/ShaderParam.hpp>

namespace libng {

class Material {
public:
private:
  Shader* shader;
  ShaderParam* param;
};

} // namespace libng