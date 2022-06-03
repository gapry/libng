#include <log/log.hpp>
#include <file/File.hpp>
#include <file/FilePath.hpp>
#include <file/Directory.hpp>

#include <libcxx/util/fmt.hpp>
#include <libcxx/util/util.hpp>

#include <compiler/json/JSONLexer.hpp>

#include <compiler/shader/ShaderCompilerUtil.hpp>
#include <compiler/shader/ShaderCompiler.hpp>

int main(void) {
  LIBNG_LOG("{}{}\n", "[log] ", libng::ShaderCompilerUtil::onGetCurrentDir());

  libng::String file = libng::ShaderCompilerUtil::onGetCurrentDir();
  libng::String path = libng::FilePath::dirname(file);

#if 1
  path.append("/../../Assets");
#else
  path.append("/../../../../Assets");
#endif

  libng::Directory::setCurrent(path);
  LIBNG_LOG("[compiler] path = {}", path);

  auto dir = libng::Directory::getCurrent();
  LIBNG_LOG("[compiler] dir = {}", dir);

  libng::JSONLexer jsonLexer;
  jsonLexer.nextChar();

  libng::ShaderCompiler shaderCompiler;
  shaderCompiler.run();
  return 0;
}