#pragma once

#include <libng_core/libcxx/util/util.hpp>
#include <libng_core/file/MemMapFile.hpp>
#include <libng_render/material/ShaderInfo.hpp>
#include <libng_compiler/shader/ShaderLexer.hpp>

namespace libng {

class ShaderParser : public ShaderLexer {
public:
  void _readShader();
  void _readProperties();
  void _readProperty();
  void _readPass();

  ShaderInfo* _outInfo = nullptr;
};

} // namespace libng