#include <compiler/shader/ShaderCompiler.hpp>

#include <log/log.hpp>
#include <file/FilePath.hpp>
#include <file/Directory.hpp>
#include <libcxx/string.hpp>

namespace libng {

ShaderCompiler::ShaderCompiler() {
  _file = getExecutableFilename();
  LIBNG_LOG("{} {}\n", __LIBNG_PRETTY_FUNCTION__, _file);

  _path = FilePath::dirname(_file);
  LIBNG_LOG("{} {}\n", __LIBNG_PRETTY_FUNCTION__, _path);

  libng::String configPath;
#if 1
  configPath = "\\..\\..\\Assets"; // Visual Stdio Code
#else
  configPath = "/../../../../Assets"; // Visual Stdio
#endif
  _path.append(configPath);

  Directory::setCurrent(_path);
  LIBNG_LOG("{} {}\n", __LIBNG_PRETTY_FUNCTION__, _path);

  _proj = ProjectSettings::instance();
  _proj->setProjectRoot(_path);
}

ShaderCompiler::~ShaderCompiler() {
  if (!_proj) {
    _proj = nullptr;
  }
}

void ShaderCompiler::onRun() {
  ShaderInfo info;
  StrView shaderFilename = "Assets/Shaders/test.shader";
  String outputPath      = Fmt("LocalTemp/Imported/{}", shaderFilename);
  Directory::create(outputPath);

  readFile(info, shaderFilename);

  LIBNG_LOG("{}\n", __LIBNG_PRETTY_FUNCTION__);
}

void ShaderCompiler::readFile(ShaderInfo& outInfo, StrView filename) {
  // _memMapfile.open(filename);
  // readMem(outInfo, _memMapfile, filename);
  //
  // LIBNG_LOG("{}\n", __LIBNG_PRETTY_FUNCTION__);
}

void ShaderCompiler::readMem(ShaderInfo& outInfo, ByteSpan data, StrView filename) {
  // outInfo.clear();
  // _outInfo = &outInfo;

  // lexer->reset(data, filename);
  // if (lexer->_token.isIdentifier("Shader")) {
  //   parser->_readShader();
  // } else {
  // }

  LIBNG_LOG("{}\n", __LIBNG_PRETTY_FUNCTION__);
}

} // namespace libng