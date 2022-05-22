#include <log/log.hpp>
#include <compiler/ShaderCompilerUtil.hpp>

int main(void) {
  LIBNG_LOG("{}{}\n", "[log] ", libng::ShaderCompilerUtil::onGetCurrentDir());
  return 0;
}