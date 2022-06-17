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

    // case 0: the next token doesn't exist
    if (!_ch) {
      return false;
    }

    // case 1: single line comment
    if (_ch == '#') {
      _parseCommentSingleLine();
      continue;
    }

    // case 2: comment block
    if (_ch == '/') {
      nextChar();
      if (_ch == '*') {
        _parseCommentBlock();
        continue;
      }
      if (_ch == '/') {
        _parseCommentSingleLine();
        continue;
      }
      _token.type = TokenType::Operator;
      _token.str  = '/';
      return true;
    }

    // final case: it must be the operator
    _token.type = TokenType::Operator;
    // update the _token before get next char;
    _token.str += _ch;
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

void ShaderLexer::_parseCommentSingleLine() {
  LIBNG_LOG("{}\n", __LIBNG_FUNCTION__);

  nextChar();
  for (;;) {
    // case 0: no char
    if (!_ch) {
      return;
    }
    // case 1: new line
    if (_ch == '\n') {
      nextChar();
      return;
    } else {
      // case 2: get next char diectly
      nextChar();
    }
  }
}

void ShaderLexer::_parseCommentBlock() {
  LIBNG_LOG("{}\n", __LIBNG_FUNCTION__);

  nextChar();
  for (;;) {
    // case 0: no char
    if (!_ch) {
      return;
    }
    // case 1: comment operator
    if (_ch == '*') {
      nextChar();
      // case 2: the end of the comment
      if (_ch == '/') {
        nextChar();
        return;
      } else {
        // case 3: get next char diectly
        nextChar();
      }
    }
  }
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

void ShaderLexer::_error(StrView msg) {
  // ToDo
  LIBNG_ERROR("{}\n", __LIBNG_FUNCTION__);
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

void ShaderLexer::Token::onFormat(fmt::format_context& ctx) const {
  fmt::format_to(ctx.out(), "({}, {})", type, str);
}

} // namespace libng