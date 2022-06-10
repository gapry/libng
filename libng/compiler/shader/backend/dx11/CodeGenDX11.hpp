#pragma once

#include <compiler/shader/ShaderCodeGen.hpp>
#include <libcxx/string_view.hpp>
#include <libcxx/span.hpp>
#include <file/MemMapFile.hpp>
#include <platform/graphics.hpp>
#include <renderer/material/ShaderStageMask.hpp>
#include <renderer/material/ShaderStageInfo.hpp>
#include <renderer/type/RenderDataType.hpp>
#include <renderer/backend/dx11/DX11Util.hpp>
#include <renderer/backend/dx11/TypeDX11.hpp>

namespace libng {

class CodeGenDX11 : public ShaderCodeGen {
  using Util     = DX11Util;
  using DataType = RenderDataType;

public:
  CodeGenDX11(CreateDesc& desc);

private:
  struct Reflect {
    void execute();

  private:
    void _inputs();
    void _constBuffers();
    void _textures();
    void _samplers();
  };

  StrView _outFilename;
  ByteSpan _ByteToChar;
  ShaderStageMask _stage;
  StrView _profile;
  // ShaderStageInfo& outInfo; // Issue: references must be initialized
  ID3D11ShaderReflection* _refect;
  // D3D11_SHADER_DESC& desc;
};

} // namespace libng