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
}

void ShaderParser::_readProperties() {
}

void ShaderParser::_readProperty() {
}

void ShaderParser::_readPass() {
}

} // namespace libng