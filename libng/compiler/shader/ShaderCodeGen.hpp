#pragma once

#include <renderer/material/ShaderStage.hpp>
#include <renderer/material/ShaderUtil.hpp>
#include <libcxx/string_view.hpp>

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
