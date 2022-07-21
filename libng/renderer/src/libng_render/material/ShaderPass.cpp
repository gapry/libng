#include <libng_render/material/ShaderPass.hpp>

namespace libng {

ShaderPass::ShaderPass(Shader* shader, ShaderInfo::Pass& info)
  : _shader(shader)
  , _info(&info) {
}

ShaderVertexStage* ShaderPass::vertexStage() {
  return _vertexStage;
}

ShaderPixelStage* ShaderPass::pixelStage() {
  return _pixelStage;
}

const ShaderInfo::Pass* ShaderPass::info() const {
  return _info;
}

} // namespace libng