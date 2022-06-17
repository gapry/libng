#include <libng_compiler/shader/ShaderLexer.hpp>

namespace libng {

void ShaderLexer::reset(ByteSpan source, StrView filename) {
  LIBNG_LOG("[{}] source size = {}, filename = {}\n", __LIBNG_FUNCTION__, source.size(), filename);

  reset(StrView_make(source), filename);
}

void ShaderLexer::reset(StrView source, StrView filename) {
  LIBNG_LOG("[{}] source = \n{}\n\nfilename = {}\n", __LIBNG_FUNCTION__, source, filename);

  _source   = source;
  _filename = filename;
  _cur      = _source.data();
  _ch       = 0;
  _col      = 0;
  _line     = 1;

  nextChar();
  nextToken();
}

bool ShaderLexer::nextChar() {
  LIBNG_LOG("{}\n", __LIBNG_FUNCTION__);

  return false;
}

bool ShaderLexer::nextToken() {
  LIBNG_LOG("{}\n", __LIBNG_FUNCTION__);

  return false;
}

ShaderLexer::Token::Token() {
  this->setNone();
}

ShaderLexer::Token::~Token() {
  this->setNone();
}

void ShaderLexer::Token::setNone() {
  type = TokenType::None;
  str.clear();
}

bool ShaderLexer::_parseIdentifier() {
  return false;
}

bool ShaderLexer::_parseNumber() {
  return false;
}

bool ShaderLexer::_parseString() {
  return false;
}

bool ShaderLexer::_parseCommentBlock() {
  return false;
}

bool ShaderLexer::_parseCommentString() {
  return false;
}

bool ShaderLexer::_parseToken() {
  return false;
}

void ShaderLexer::Token::onFormat(fmt::format_context& ctx) const {
  fmt::format_to(ctx.out(), "({}, {})", type, str);
}

void ShaderLexer::_error(StrView msg) {
  // ToDo
  LIBNG_ERROR("{}\n", __LIBNG_FUNCTION__);
}

} // namespace libng