#pragma once

#include <libcxx/util/util.hpp>
#include <file/MemMapFile.hpp>

#include <renderer/material/ShaderInfo.hpp>

namespace libng {

class ShaderParser {
public:
  // protected: // Issue
  bool _parseIdentifier();
  bool _parseNumber();
  bool _parseString();
  bool _parseCommentBlock();
  bool _parseCommentString();
  bool _parseToken();

  void _readShader();
  void _readProperties();
  void _readProperty();
  void _readPass();

  ShaderInfo* _outInfo = nullptr;
};

} // namespace libng