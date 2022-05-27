#pragma once

namespace libng {

enum TokenType
{
  ShaderNone,
  ShaderIdentifier,
  ShaderNumber,
  ShaderString,
  ShaderOperator,
  ShaderNewline,
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