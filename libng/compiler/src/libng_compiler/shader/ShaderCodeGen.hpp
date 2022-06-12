#pragma once

#include <libng_core/libcxx/string.hpp>
#include <libng_core/libcxx/string_view.hpp>
#include <libng_render/material/ShaderStage.hpp>
#include <libng_render/material/ShaderUtil.hpp>

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

  void setApiType(String& apiType);

protected:
  static ShaderCodeGen* s_codeGen;

private:
  String _apiType;
};

} // namespace libng
