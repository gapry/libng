#include <log/log.hpp>
#include <file/FilePath.hpp>
#include <libcxx/util/util.hpp>
#include <compiler/ShaderCompilerUtil.hpp>
#include <compiler/ShaderCompiler.hpp>

int main(void) {
  LIBNG_LOG("{}{}\n", "[log] ", libng::ShaderCompilerUtil::onGetCurrentDir());

  libng::String file = libng::getExecutableFilename();
  libng::String path = libng::FilePath::dirname(file);

#if 1
  libng::path.append("/../../Assets");
#else
  libng::path.append("/../../../../Assets");
#endif

  libng::Directory::setCurrent(path);

  auto dir = libng::Directory::getCurrent();
  LIBNG_LOG("dir = {}", dir);

  libng::ShaderCompiler compiler;
  compiler.execute(file);
  return 0;
}