#pragma once

#include <types/noncopyable.hpp>
#include <libcxx/util/util.hpp>
#include <libcxx/util/fmt.hpp>

namespace libng {

class ShaderLexer : public NonCopyable {
public:
  enum class TokenType
  {
    None,
    Identifier,
    Number,
    String,
    Operator,
    Newline,
  };

  struct Token {
    TokenType type = TokenType::None;
    String str;

    // clang-format off
    bool isNone()                const { return TokenType::None == type; }

    bool isIdentifier()          const { return TokenType::Identifier == type; }
    bool isIdentifier(StrView s) const { return TokenType::Identifier == type && s == str; }

    bool isNumber()              const { return TokenType::Number == type; }

    bool isString()              const { return TokenType::String == type; }
    bool isString(StrView s)     const { return TokenType::String == type && s == str; }

    bool isOperator()            const { return TokenType::Operator == type;}
    bool isOperator(StrView s)   const { return TokenType::String == type && s == str; }
    
    bool isNewLine()             const { return TokenType::Newline == type;}
    // clang-format on

    void setNone();

    void onFormat(fmt::format_context& ctx) const;
  };
};

} // namespace libng