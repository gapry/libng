#include <compiler/ShaderLexer.hpp>

namespace libng {

int ShaderLexer::lookahead(void) {
  int chr = _getNextChar();
  return chr;
}

int ShaderLexer::skip(void) {
  int chr = lookahead();

  bool isSpace   = ' ' == chr;
  bool isNewline = '\n' == chr;
  bool isEnter   = '\r' == chr;
  bool isFeed    = '\f' == chr;

  bool isSkip = isSpace || isNewline || isEnter || isFeed;

  while (isSkip) {
    chr = lookahead();
  }
  return chr;
}

void ShaderLexer::execute(TokenType tokenType) {
  // int chr = skip();
  switch (tokenType) {
    case TokenType::Identifier: break;
    case TokenType::Number: break;
    case TokenType::String: break;
    case TokenType::Operator: break;
    case TokenType::Newline: break;
    default: break;
  }
}

char ShaderLexer::_getNextChar(void) {
  return ' ';
}

} // namespace libng