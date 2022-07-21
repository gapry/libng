#include <libng_render/material/Shader.hpp>

namespace libng {

Shader::Shader(StrView filename)
  : _filename(filename) {
  auto* proj        = ProjectSettings::instance();
  auto infoFilename = Fmt("{}/{}/info.json", proj->importedPath(), filename);
  JsonUtil::readFile(infoFilename, _info);
}

Shader::~Shader() {
  auto* renderer = Renderer::instance();
  renderer->onShaderDestory(this);
}

const String& Shader::filename() const {
  return _filename;
}

const ShaderInfo* Shader::info() const {
  return &_info;
}

Span<UPtr<ShaderPass>> Shader::passes() {
  return _passes;
}

} // namespace libng