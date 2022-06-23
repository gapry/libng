#include <libng_core/file/Directory.hpp>
#include <libng_core/file/FilePath.hpp>
#include <libng_core/file/JsonFile.hpp>
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
    String file       = getExecutableFilename();
    String path       = FilePath::DirName(file);
    String assetsPath = FilePath::GetAssetsPath();
    path.append(assetsPath);
    Directory::setCurrent(path);

    auto* proj = ProjectSettings::instance();
    proj->setProjectRoot(path);
  }

  StrView shaderFilename = "Assets/Shaders/test/case02.shader";
  String outputPath      = Fmt("Assets/LocalTemp/Imported/{}", shaderFilename);
  Directory::create(outputPath);

  ShaderInfo info;
  {
    LIBNG_LOG("prop size = {}\n", info.props.size());
    LIBNG_LOG("pass size = {}\n", info.passes.size());

    // Shader Input
    ShaderParser parser;
    parser.readFile(info, shaderFilename);

    LIBNG_LOG("prop size = {}\n", info.props.size());
    LIBNG_LOG("pass size = {}\n", info.passes.size());

    // JSON Output
    auto jsonFilename = Fmt("{}/info.json", outputPath);
    JsonFile::write(jsonFilename, info, true);
  }

  // DX11 CodeGen
  {
    size_t passIndex = 0;
    for (auto& pass : info.passes) {
      auto passOutPath = Fmt("{}/dx11/pass{}", outputPath, passIndex);
      LIBNG_LOG("passPath = {}\n", passOutPath);

      CodeGenDX11 codegen;
      {
        if (pass.vsFunc.size()) {
          LIBNG_LOG("pass[{}] : {}\n", passIndex, "vertex shader");

          codegen.Execute(passOutPath,             //
                          ShaderStageMask::Vertex, //
                          shaderFilename,          //
                          pass.vsFunc);            //
        }

        if (pass.psFunc.size()) {
          LIBNG_LOG("pass[{}] : {}\n", passIndex, "pixel shader");

          codegen.Execute(passOutPath,            //
                          ShaderStageMask::Pixel, //
                          shaderFilename,         //
                          pass.psFunc);           //
        }
      }
      passIndex++;
    }
  }
}

} // namespace libng