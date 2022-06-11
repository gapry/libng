#include <libng_core/platform/os.hpp>
#include <libng_core/exception/error.hpp>
#include <libng_compiler/shader/ShaderCodeGen.hpp>
#include <libng_compiler/shader/backend/dx11/CodeGenDX11.hpp>
#include <libng_compiler/shader/backend/opengl/CodeGenOpenGL.hpp>

namespace libng {

ShaderCodeGen* ShaderCodeGen::s_codeGen = nullptr;

ShaderCodeGen::CreateDesc::CreateDesc(StrView filename, ShaderStage stage, StrView src, StrView entry) {
#if LIBNG_OS_WINDOWS
  apiType = ApiType::DX11;
#else
  apiType = ApiType::OpenGL;
#endif

  outFilename = filename;
  shaderStage = stage;
  srcFilename = src;
  entryFunc   = entry;
}

ShaderCodeGen* ShaderCodeGen::create(CreateDesc& desc) {
  ShaderCodeGen* codeGen = nullptr;
  // clang-format off
  switch (desc.apiType) {
    case ApiType::DX11:   codeGen = new CodeGenDX11(desc);   break;
    case ApiType::OpenGL: codeGen = new CodeGenOpenGL(desc); break;
    default: LIBNG_ERROR("{}\n", "Unsupported Shader Format");
  }
  // clang-format on
  return codeGen;
}

} // namespace libng
