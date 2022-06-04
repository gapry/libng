#include <compiler/shader/ShaderCompiler.hpp>

#include <log/log.hpp>
#include <file/FilePath.hpp>
#include <file/Directory.hpp>

namespace libng {

ShaderCompiler::ShaderCompiler() {
  _file = getExecutableFilename();
  LIBNG_LOG("[{}] {}\n", __LIBNG_PRETTY_FUNCTION__, _file);

  _path = FilePath::dirname(_file);
  LIBNG_LOG("[{}] {}\n", __LIBNG_PRETTY_FUNCTION__, _path);

#if 1
  _path.append("\\..\\..\\Assets"); // VS Code
#else
  _path.append("/../../../../Assets"); // VS
#endif

  Directory::setCurrent(_path);
  LIBNG_LOG("[{}] {}\n", __LIBNG_PRETTY_FUNCTION__, _path);

  _proj = ProjectSettings::instance();
  _proj->setProjectRoot(_path);
}

ShaderCompiler::~ShaderCompiler() {
  if (!_proj) {
    _proj = nullptr;
  }
}

void ShaderCompiler::onRun() {
}

void ShaderCompiler::readFile(ShaderInfo& outInfo, StrView filename) {
}

void ShaderCompiler::readMem(ShaderInfo& outInfo, ByteSpan data, StrView filename) {
}

} // namespace libng