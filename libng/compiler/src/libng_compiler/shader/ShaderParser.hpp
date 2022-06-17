#pragma once

#include <libng_core/libcxx/span.hpp>
#include <libng_core/libcxx/string_view.hpp>
#include <libng_core/log/log.hpp>
#include <libng_core/types/function.hpp>
#include <libng_core/file/MemMapFile.hpp>
#include <libng_render/material/ShaderInfo.hpp>
#include <libng_compiler/shader/ShaderLexer.hpp>

namespace libng {

class ShaderParser : public ShaderLexer {
public:
  void readFile(ShaderInfo& outInfo, StrView filename);
  void readMem(ShaderInfo& outInfo, ByteSpan data, StrView filename);

private:
  void _readShader();
  void _readProperties();
  void _readProperty();
  void _readPass();

  MemMapFile _memMapFile;
  ShaderInfo* _outInfo = nullptr;
};

} // namespace libng