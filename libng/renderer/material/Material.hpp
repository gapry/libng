#pragma once

#include <libcxx/util/util.hpp>

#include <renderer/shader/Shader.hpp>
#include <renderer/shader/ShaderParam.hpp>

namespace libng {

class Material {
public:
  template<typename T>
  void setParam(const String& name, const T value);

private:
  Shader* shader;
  ShaderParam* param;
  Vector_<uint8_t, 32> dirtiedCBuff;
};

template<typename T>
void Material::setParam(const String& name, const T value) {
}

} // namespace libng