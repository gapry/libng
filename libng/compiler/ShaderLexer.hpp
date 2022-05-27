#pragma once

namespace libng {

enum class ShaderLexerTokenType
{
  None,
  Identifier,
  Number,
  String,
  Operator,
  Newline,
};

class ShaderLexer {
public:
  using TokenType = ShaderLexerTokenType;

  int lookahead(void);

  int skip(void);

  void execute(TokenType token);

private:
  char _getNextChar();
};

} // namespace libng