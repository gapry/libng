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

  // clang-format off
  bool isDigit(char c)     { return c >= '0' && c <= '9';             }
  bool isLowerCase(char c) { return c >= 'a' && c <= 'z';             }
  bool isUpperCase(char c) { return c >= 'A' && c <= 'Z';             }
  bool isAlpha(char c)     { return isLowerCase(c) || isUpperCase(c); }
  // clang-format on

  // clang-format off
  const char* cur() const { return _cur;    } 
  StrView source()  const { return _source; }
  size_t line()     const { return _line;   }
  size_t col()      const { return _col;    }
  // clang-format on

private:
  Token _token;
  String _filename;
  StrView _source;

  const char* _cur = nullptr;
  char _ch         = 0;
  size_t _col      = 0;
  size_t _line     = 0;
};

} // namespace libng