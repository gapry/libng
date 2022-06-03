#pragma once

#include <compiler/shader/ShaderCompilerUtil.hpp>

#include <libcxx/util/util.hpp>

namespace libng {

class ShaderCodeGen {
public:
  enum class ApiType
  {
    None,
    DX11,
    OpenGL,
  };

  struct CreateDesc {
    CreateDesc(StrView outFilename, ShaderStage shaderStage, StrView srcFilename, StrView entryFunc);

    ApiType apiType;
    StrView outFilename;
    ShaderStage shaderStage;
    StrView srcFilename;
    StrView entryFunc;
  };

  static ShaderCodeGen* create(CreateDesc& desc);

protected:
  static ShaderCodeGen* s_codeGen;
};

} // namespace libng
