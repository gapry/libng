#include <log/log.hpp>
#include <types/function.hpp>
#include <file/File.hpp>
#include <file/FilePath.hpp>
#include <file/Directory.hpp>
#include <libcxx/fmt.hpp>
#include <libcxx/string.hpp>
#include <compiler/json/JSONLexer.hpp>
#include <compiler/shader/ShaderCompiler.hpp>

int main(void) {
  LIBNG_LOG("{} {}\n", __LIBNG_PRETTY_FUNCTION__, libng::Directory::getCurrent());

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
  LIBNG_LOG("{} path = {}", __LIBNG_PRETTY_FUNCTION__, path);

  auto dir = libng::Directory::getCurrent();
  LIBNG_LOG("{} dir = {}", __LIBNG_PRETTY_FUNCTION__, dir);

  libng::JSONLexer jsonLexer;
  jsonLexer.nextChar();

  libng::ShaderCompiler shaderCompiler;
  shaderCompiler.run();
  return 0;
}