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
  LIBNG_LOG("[begin] {}, _ch = {}, *_cur = {}, _col = {}\n", __LIBNG_FUNCTION__, _ch, *_cur, _col);

  _ch = 0;
  if (!_cur || _cur >= _source.end()) {
    return false;
  }

  _ch = *_cur;
  _cur++;
  _col++;

  if (_ch == '\n') {
    _line++;
    _col = 0;
  }

  LIBNG_LOG("[end] {}, _ch = {}, *_cur = {}, _col = {}\n", __LIBNG_FUNCTION__, _ch, *_cur, _col);

  return true;
}

bool ShaderLexer::nextToken() {
  LIBNG_LOG("{}\n", __LIBNG_FUNCTION__);

  if (!_nextToken()) {
    return false;
  }
  return true;
}

bool ShaderLexer::_nextToken() {
  LIBNG_LOG("{}\n", __LIBNG_FUNCTION__);

  _token.setNone();
  for (;;) {
    trimSpaces();
    nextChar();
    return true;
  }
}

void ShaderLexer::trimSpaces() {
  LIBNG_LOG("{}\n", __LIBNG_FUNCTION__);

  for (;;) {
    if (_ch == ' ' || _ch == '\t' || _ch == '\r') {
      nextChar();
    } else {
      break;
    }
  }
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