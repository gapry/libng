#include <log/log.hpp>
#include <shader/ShaderCompiler.hpp>
#include <shader/ShaderUtil.hpp>

int main(void) {
  LIBNG_LOG("{}{}\n", "[log] ", libng::shader::onGetCurrentDir());
  return 0;
}