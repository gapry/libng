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

  template<class E>
  void _readEnum(E& v);

  MemMapFile _memMapFile;
  ShaderInfo* _outInfo = nullptr;
};

template<class E>
LIBNG_INLINE void ShaderParser::_readEnum(E& v) {
  if (!token().isIdentifier()) {
    errorUnexpectedToken();
    return;
  }
  if (!enumTryParse(v, _token.str)) {
    error("read enum [{}]", _token.str);
  }
  nextToken();
}

} // namespace libng