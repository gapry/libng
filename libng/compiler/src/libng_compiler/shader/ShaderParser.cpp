#include <libng_compiler/shader/ShaderParser.hpp>

namespace libng {

void ShaderParser::readFile(ShaderInfo& outInfo, StrView filename) {
  LIBNG_LOG("[{}] filename = {}\n", __LIBNG_FUNCTION__, filename);

  _memMapFile.open(filename);
  readMem(outInfo, _memMapFile, filename);
}

void ShaderParser::readMem(ShaderInfo& outInfo, ByteSpan data, StrView filename) {
  LIBNG_LOG("[{}] filesize = {}\n", __LIBNG_FUNCTION__, data.size());
}

void ShaderParser::_readShader() {
}

void ShaderParser::_readProperties() {
}

void ShaderParser::_readProperty() {
}

void ShaderParser::_readPass() {
}

} // namespace libng