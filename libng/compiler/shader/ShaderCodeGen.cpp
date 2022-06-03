#include <compiler/shader/ShaderCodeGen.hpp>
#include <compiler/shader/backend/dx11/CompilerDX11.hpp>
#include <compiler/shader/backend/opengl/CompilerOpenGL.hpp>

#include <platform/os.hpp>
#include <exception/error.hpp>

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
  switch (desc.apiType) {
    case ApiType::DX11: codeGen = new CompilerDX11(desc); break;
    case ApiType::OpenGL: codeGen = new CompilerOpenGL(desc); break;
    default: LIBNG_ERROR("{}\n", "Unsupported Shader Format");
  }
  return codeGen;
}

} // namespace libng
