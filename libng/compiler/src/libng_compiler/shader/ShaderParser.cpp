#include <libng_compiler/shader/ShaderParser.hpp>

namespace libng {

void ShaderParser::readFile(ShaderInfo& outInfo, StrView filename) {
  LIBNG_LOG("[{}] filename = {}\n", __LIBNG_FUNCTION__, filename);

  _memMapFile.open(filename);
  readMem(outInfo, _memMapFile, filename);
}

void ShaderParser::readMem(ShaderInfo& outInfo, ByteSpan data, StrView filename) {
  LIBNG_LOG("[{}] filesize = {}\n", __LIBNG_FUNCTION__, data.size());

  outInfo.clear();
  _outInfo = &outInfo;
  reset(data, filename);

  LIBNG_LOG("token = {}\n", _token);

  if (_token.isIdentifier("Shader")) {
    _readShader();
  } else {
    error("missing Shader tag");
  }
}

void ShaderParser::_readShader() {
  LIBNG_LOG("{}\n", __LIBNG_FUNCTION__);

  nextToken();
  expectOperator("{");

  // clang-format off
  for(;;) {
    if(_token.isOperator("}"))            { nextToken(); break; }
    if(_token.isNewLine())                { nextToken(); continue; }
    if(_token.isIdentifier("Properties")) { _readProperties(); continue; }
    if(_token.isIdentifier("Pass"))       { _readPass(); continue; }
    return errorUnexpectedToken();
  }
  // clang-format on
}

/*
 * Properties {
 *   Float s   = 0.5
 *   Vec4f v   = {1.2, 2.3, 3.4, 4.5}
 *
 *   [DisplayName="Color Test"]
 *   Color4f c = {1.0, 1.0, 1.0, 1.0}
 * }
 */
void ShaderParser::_readProperties() {
  LIBNG_LOG("{}\n", __LIBNG_FUNCTION__);

  nextToken();
  expectOperator("{");
  for (;;) {
    skipNewlineTokens();
    if (_token.isOperator("}")) {
      nextToken(); // Issue
      break;
    }
    _readProperty();
  }
}

void ShaderParser::_readProperty() {
  LIBNG_LOG("{}\n", __LIBNG_FUNCTION__);

  auto& o = _outInfo->props.emplace_back();

  // case: optional attributes
  if (_token.isOperator("[")) {
    nextToken();
    while (!_token.isNone()) {
      skipNewlineTokens();
      if (_token.isIdentifier("DisplayName")) {
        nextToken();
        expectOperator("=");
        readString(o.displayName);
      }
      if (_token.isOperator("]")) {
        nextToken();
        break;
      }
      expectOperator(",");
    }
  }
  skipNewlineTokens();

  {
    _readEnum(o.propType);  // prop type
    readIdentifier(o.name); // prop name
  }

  // optional defaultValue
  if (_token.isOperator("=")) {
    nextToken();
    while (!_token.isNone()) {
      if (_token.isNewLine()) {
        break;
      }
      o.defaultValue += _token.str;
      nextToken();
    }
  }

  if (!_token.isNewLine()) {
    errorUnexpectedToken();
  }
  nextToken();
}

/**
 * Pass {
 *   // Queue       "Transparent"
 * 	 // Cull        None
 *   //
 * 	 // BlendRGB
 * 	 // BlendAlpha
 *   //
 * 	 // DepthTest   Always
 * 	 // DepthWrite  false
 *   //
 *   VsFunc         vs_main
 *   PsFunc         ps_main
 * }
 */
void ShaderParser::_readPass() {
  LIBNG_LOG("{}\n", __LIBNG_FUNCTION__);

  nextToken();
  auto& o = _outInfo->passes.emplace_back();

  if (_token.isString()) {
    readString(o.name);
  }
  expectOperator("{");

  // clang-format off
  for(;;) {
    if(_token.isOperator("}"))        { nextToken(); break; }
    if(_token.isNewLine())            { nextToken(); continue; }
    if(_token.isIdentifier("VsFunc")) { nextToken(); readIdentifier(o.vsFunc); continue; }
    if(_token.isIdentifier("PsFunc")) { nextToken(); readIdentifier(o.psFunc); continue; }
    return errorUnexpectedToken();
  }
  // clang-format on
}

} // namespace libng