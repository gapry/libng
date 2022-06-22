#include <libng_core/file/Directory.hpp>
#include <libng_core/file/FilePath.hpp>
#include <libng_core/libcxx/string.hpp>
#include <libng_core/log/log.hpp>

#include <libng_compiler/shader/ShaderCompiler.hpp>
#include <libng_compiler/shader/ShaderParser.hpp>
#include <libng_compiler/shader/backend/dx11/CodeGenDX11.hpp>

namespace libng {

ShaderCompiler::ShaderCompiler() {
  _apiType.clear();
}

ShaderCompiler::~ShaderCompiler() {
  _apiType.clear();
}

void ShaderCompiler::onRun(int argc, char** argv) {
  if (argc != 2) {
    LIBNG_ERROR("{}\n", "console arguments aren't correct!");
  }

  if (argv[1] == nullptr) {
    LIBNG_ERROR("{}\n", "argv[1] is wrong!");
  }

  _apiType = argv[1];
  LIBNG_LOG("The Graphics API is {}\n", _apiType);

  _apiType.clear();

  {
    String file = getExecutableFilename();
    String path = FilePath::dirname(file);

    String assetsPath;
#if LIBNG_IDE_VSC
    assetsPath = "\\..\\..\\Assets";
#elif LIBNG_IDE_VS
    assetsPath = "/../../../../Assets";
#endif
    path.append(assetsPath);
    Directory::setCurrent(path);

    auto* proj = ProjectSettings::instance();
    proj->setProjectRoot(path);
  }

  ShaderInfo info;

  StrView shaderFilename = "Assets/Shaders/test/case01.shader";
  String outputPath      = Fmt("Assets/LocalTemp/Imported/{}", shaderFilename);
  Directory::create(outputPath);

  // Shader Input
  {
    ShaderParser parser;
    parser.readFile(info, shaderFilename);
  }
  // JSON Output
  { auto jsonFilename = Fmt("{}/test_case01_shader.json", outputPath); }
}

} // namespace libng