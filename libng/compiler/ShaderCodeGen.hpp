#pragma once

#include <libcxx/util/util.hpp>
#include <compiler/ShaderCompilerUtil.hpp>

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
