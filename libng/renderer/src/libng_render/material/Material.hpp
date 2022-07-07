#pragma once

#include <libng_render/material/MaterialPass.hpp>
#include <libng_render/material/Shader.hpp>

namespace libng {

class Material : public RefCountBase {
public:
  using Pass = MaterialPass;

  Material();
  virtual ~Material();

  template<typename T>
  void setParam(const String& name, const T value);

protected:
  Vector_<UPtr<Pass>, 2> _passes;
  SPtr<Shader> _shader;
};

template<typename T>
void Material::setParam(const String& name, const T value) {
}

} // namespace libng