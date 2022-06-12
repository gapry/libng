#include <libng_core/log/log.hpp>
#include <libng_core/file/FilePath.hpp>
#include <libng_core/file/Directory.hpp>
#include <libng_core/libcxx/string.hpp>
#include <libng_compiler/shader/ShaderCompiler.hpp>

namespace libng {

ShaderCompiler::ShaderCompiler() {
  _apiType.clear();
  _assetsPath.clear();

  _file = getExecutableFilename();
  _path = FilePath::dirname(_file);


#if LIBNG_IDE_VSC
  _assetsPath = "\\..\\..\\Assets";
#elif LIBNG_IDE_VS
  _assetsPath = "/../../../../Assets";
#endif
  _path.append(_assetsPath);

  Directory::setCurrent(_path);

  _proj = ProjectSettings::instance();
  _proj->setProjectRoot(_path);
}

ShaderCompiler::~ShaderCompiler() {
  if(!_proj) {
    _proj = nullptr;
  }
  _file.clear();
  _path.clear();
  _apiType.clear();
}

void ShaderCompiler::onRun(int argc, char** argv) {
  if(argc != 2) {
    LIBNG_ERROR("{}\n", "console arguments aren't correct!");
  }

  if(argv[1] == nullptr) {
    LIBNG_ERROR("{}\n", "argv[1] is wrong!");
  }

  _apiType = argv[1];
  LIBNG_LOG("GFX API = {}", _apiType);

  StrView shaderFilename = "Assets/Shaders/test/case01.shader";
  String outputPath      = Fmt("Assets/LocalTemp/Imported/{}", shaderFilename);
  Directory::create(outputPath);

  ShaderInfo info;
  readFile(info, shaderFilename);
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
}

} // namespace libng