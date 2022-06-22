#include <libng_core/exception/error.hpp>
#include <libng_core/platform/os.hpp>

#include <libng_compiler/shader/ShaderCodeGen.hpp>
#include <libng_compiler/shader/backend/dx11/CodeGenDX11.hpp>
#include <libng_compiler/shader/backend/opengl/CodeGenOpenGL.hpp>

namespace libng {

ShaderCodeGen::ShaderCodeGen() {
  resetApi();
}

ShaderCodeGen::~ShaderCodeGen() {
  resetApi();
}

void ShaderCodeGen::resetApi() {
  _apiType.clear();
}

} // namespace libng
