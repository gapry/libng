#include <log/log.hpp>
#include <file/File.hpp>
#include <file/FilePath.hpp>
#include <file/Directory.hpp>
#include <libcxx/util/fmt.hpp>
#include <libcxx/util/util.hpp>
#include <compiler/ShaderCompilerUtil.hpp>
#include <compiler/ShaderCompiler.hpp>

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

  libng::ShaderCompiler compiler;
  compiler.execute(file);
  return 0;
}