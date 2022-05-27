#pragma once

namespace libng {

enum TokenType
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
  int lookahead(void);

  int skip(void);

  void execute(TokenType token);

private:
  char _getNextChar();
};

} // namespace libng