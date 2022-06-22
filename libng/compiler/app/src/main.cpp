#include <libng_core/file/Directory.hpp>
#include <libng_core/file/File.hpp>
#include <libng_core/file/FilePath.hpp>
#include <libng_core/libcxx/fmt.hpp>
#include <libng_core/libcxx/string.hpp>
#include <libng_core/log/log.hpp>
#include <libng_core/types/function.hpp>

#include <libng_compiler/json/JSONLexer.hpp>
#include <libng_compiler/shader/ShaderCompiler.hpp>

void pre_run() {
  libng::String file = libng::Directory::getCurrent();
  libng::String path = libng::FilePath::dirname(file);

  libng::String configPath;
#if LIBNG_IDE_VSC
  configPath = "\\..\\..\\Assets";
#elif LIBNG_IDE_VS
  configPath = "/../../../../Assets";
#endif
  path.append(configPath);

  libng::Directory::setCurrent(path);
  auto dir = libng::Directory::getCurrent();
}

int main(int argc, char** argv) {
  libng::ShaderCompiler shaderCompiler;
  shaderCompiler.run(argc, argv);
  return 0;
}