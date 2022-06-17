#include <libng_core/libcxx/util/util.hpp>
#include <libng_compiler/shader/ShaderLexer.hpp>

namespace libng {

ShaderLexer::ShaderLexer() {
  this->reset();
}

ShaderLexer::~ShaderLexer() {
  this->reset();
}

void ShaderLexer::reset() {
  _token.setNone();
  _filename.clear();
  _source.empty();

  _cur  = nullptr;
  _ch   = 0;
  _col  = 0;
  _line = 0;
}

void ShaderLexer::reset(ByteSpan source, StrView filename) {
  reset(StrView_make(source), filename);
}

void ShaderLexer::reset(StrView source, StrView filename) {
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
  return false;
}

bool ShaderLexer::nextToken() {
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

} // namespace libng