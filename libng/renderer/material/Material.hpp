#pragma once

#include <libcxx/string.hpp>
#include <libcxx/fixed_vector.hpp>
#include <renderer/material/Shader.hpp>

namespace libng {

class Material {
public:
  template<typename T>
  void setParam(const String& name, const T value);

private:
  Shader* shader;
  Vector_<uint8_t, 32> dirtiedCBuff;
};

template<typename T>
void Material::setParam(const String& name, const T value) {
}

} // namespace libng