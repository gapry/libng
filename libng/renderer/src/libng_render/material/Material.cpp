#include <libng_render/material/Material.hpp>

namespace libng {

void Material::setShader(Shader* shader) {
  if (_shader == shader) {
    return;
  }
  _shader = shader;
  _passes.clear();
  _passes.reserve(shader->passes().size());
  for (auto& shaderPass : shader->passes()) {
    UPtr<Pass> pass = onCreatePass(shaderPass.get());
    _passes.emplace_back(std::move(pass));
  }
  onSetShader();
}

} // namespace libng