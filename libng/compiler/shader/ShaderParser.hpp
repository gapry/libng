#pragma once

#include <libcxx/util/util.hpp>
#include <file/MemMapFile.hpp>

#include <renderer/material/ShaderInfo.hpp>

namespace libng {

class ShaderParser {
public:
protected:
  bool _parseIdentifier();
  bool _parseNumber();
  bool _parseString();
  bool _parseCommentBlock();
  bool _parseCommentString();

  void _readShader();
  void _readProperties();
  void _readProperty();
  void _readPass();

  ShaderInfo* _outInfo = nullptr;
};

} // namespace libng