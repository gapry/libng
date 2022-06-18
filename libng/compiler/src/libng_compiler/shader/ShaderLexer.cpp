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
  // LIBNG_LOG("[begin] {}, _ch = {}, *_cur = {}, _col = {}\n", __LIBNG_FUNCTION__, _ch, *_cur, _col);
  LIBNG_LOG("[begin] {}\n", __LIBNG_FUNCTION__);

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

  // LIBNG_LOG("[end] {}, _ch = {}, *_cur = {}, _col = {}\n", __LIBNG_FUNCTION__, _ch, *_cur, _col);
  LIBNG_LOG("[end] {}\n", __LIBNG_FUNCTION__);

  return true;
}

bool ShaderLexer::nextToken() {
  LIBNG_LOG("{}\n", __LIBNG_FUNCTION__);

  if (!_nextToken()) {
    return false;
  }
  LIBNG_LOG("{} {}\n", _line, _token);
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

    // case 4: alphabet
    if (_ch == '_' || isAlpha(_ch)) {
      return _parseIdentifier();
    }

    // case 5: digit
    if (isDigit(_ch)) {
      return _parseNumber();
    }

    // case 6: string
    if (_ch == '\"') {
      return _parseString();
    }

    // case 3: new line
    if (_ch == '\n') {
      _token.type = TokenType::Newline;
      _token.str += "<newline>";
      nextChar();
      return true;
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
  LIBNG_LOG("{}\n", __LIBNG_FUNCTION__);

  _token.type = TokenType::Identifier;
  _token.str += _ch;
  nextChar();
  while (_ch) {
    // the identifier can be combined by alphabet, digit and '_'
    if (_ch == '_' || isAlpha(_ch) || isDigit(_ch)) {
      _token.str += _ch;
      nextChar();
    } else {
      break;
    }
  }
  return true;
}

bool ShaderLexer::_parseNumber() {
  LIBNG_LOG("{}\n", __LIBNG_FUNCTION__);

  _token.type = TokenType::Number;
  _token.str += _ch;
  nextChar();

  bool hasDot = false;
  while (_ch) {
    if (_ch == '.') {
      // case: the '..' is invalid
      if (hasDot) {
        errorUnexpectedChar();
      }
      hasDot = true;
      _token.str += _ch;
      nextChar();
    } else if (isDigit(_ch)) {
      _token.str += _ch;
      nextChar();
    } else {
      break;
    }
  }
  return true;
}

bool ShaderLexer::_parseString() {
  LIBNG_LOG("{}\n", __LIBNG_FUNCTION__);

  // char* ch = '"';
  _token.type = TokenType::String;

  for (;;) {
    nextChar();
    if (_ch == '\\') { /* char* ch = '"\'; */
      nextChar();
      // clang-format off
      switch (_ch) {
        case '\\': /* char* ch = '"\\'; */
        case '/':  /* char* ch = '"\/'; */
        case '"':  /* char* ch = '""';  */ {
          _token.str += _ch;
        } break;
        case 'b': _token.str += '\b'; break;
        case 'f': _token.str += '\f'; break;
        case 'n': _token.str += '\n'; break;
        case 'r': _token.str += '\r'; break;
        case 't': _token.str += '\t'; break;
        default: error("unknown escape characher [{}]", _ch); 
      }
      // clang-format on
    } else if (_ch == '\"') { /* char* ch = '""'; */
      nextChar();
      break;
    } else {
      // case: the char isn't delimiter
      _token.str += _ch;
    }
  }
  return true;
}

void ShaderLexer::readString(String& s) {
  if (!_token.isIdentifier()) {
    errorUnexpectedToken();
  }
  s = _token.str;
  nextToken();
}

void ShaderLexer::readIdentifier(String& s) {
  if (!_token.isIdentifier()) {
    errorUnexpectedToken();
  }
  s = _token.str;
  nextToken();
}

void ShaderLexer::_error(StrView msg) {
  LIBNG_ERROR("{}\n", __LIBNG_FUNCTION__);
  // ToDo
}

void ShaderLexer::errorUnexpectedChar() {
  LIBNG_ERROR("{}\n", __LIBNG_FUNCTION__);

  error("Unexpected charactor [{}]", _ch);
}

void ShaderLexer::errorUnexpectedToken() {
  LIBNG_ERROR("{}\n", __LIBNG_FUNCTION__);

  error("Unexpected token [{}]", _token.str);
}

void ShaderLexer::expectOperator(StrView s) {
  LIBNG_ERROR("{}\n", __LIBNG_FUNCTION__);

  if (_token.isOperator(s)) {
    nextToken();
    return;
  }
  error("expected token {}", s);
}

void ShaderLexer::skipNewlineTokens() {
  LIBNG_ERROR("{}\n", __LIBNG_FUNCTION__);

  while (_token.isNewLine()) {
    nextToken();
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

void ShaderLexer::Token::onFormat(fmt::format_context& ctx) const {
  fmt::format_to(ctx.out(), "({}, {})", type, str);
}

} // namespace libng