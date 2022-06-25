#pragma once

#include <libng_core/libcxx/fixed_vector.hpp>
#include <libng_core/libcxx/string.hpp>
#include <libng_core/types/RefCountBase.hpp>
#include <libng_core/types/number.hpp>

#include <libng_render/material/Shader.hpp>

namespace libng {

class Material : public RefCountBase {
public:
  template<typename T>
  void setParam(const String& name, const T value);

private:
  Shader* shader = nullptr;
  Vector_<u8, 32> dirtiedCBuff;
};

template<typename T>
void Material::setParam(const String& name, const T value) {
}

} // namespace libng