#pragma once

#include <libng_core/exception/error.hpp>
#include <libng_core/libcxx/fmt.hpp>
#include <libng_core/libcxx/span.hpp>
#include <libng_core/libcxx/string.hpp>
#include <libng_core/libcxx/string_view.hpp>
#include <libng_core/libcxx/type_make.hpp>
#include <libng_core/log/log.hpp>
#include <libng_core/types/function.hpp>
#include <libng_core/types/noncopyable.hpp>

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

    Token();
    ~Token();

    // clang-format off
    bool isNone()                      const { return TokenType::None == type; }

    bool isIdentifier()                const { return TokenType::Identifier == type; }
    bool isIdentifier(const StrView s) const { return TokenType::Identifier == type && s == str; }

    bool isNumber()                    const { return TokenType::Number == type; }

    bool isString()                    const { return TokenType::String == type; }
    bool isString(const StrView s)     const { return TokenType::String == type && s == str; }

    bool isOperator()                  const { return TokenType::Operator == type;}
    bool isOperator(const StrView s)   const { return TokenType::Operator == type && s == str; }
    
    bool isNewLine()                   const { return TokenType::Newline == type;}
    // clang-format on

    void setNone();

    void onFormat(fmt::format_context& ctx) const;
  };

  void reset(ByteSpan source, StrView filename);
  void reset(StrView source, StrView filename);

  bool nextChar();
  bool nextToken();

  void trimSpaces();

  void skipNewlineTokens();

  // clang-format off
  bool isDigit(const char c)     const { return c >= '0' && c <= '9';             }
  bool isLowerCase(const char c) const { return c >= 'a' && c <= 'z';             }
  bool isUpperCase(const char c) const { return c >= 'A' && c <= 'Z';             }
  bool isAlpha(const char c)     const { return isLowerCase(c) || isUpperCase(c); }

  const Token& token() const { return _token; }
  // clang-format on

  template<class... Args>
  void error(const Args&... args) {
    LIBNG_LOG("{}\n", __LIBNG_FUNCTION__);

    auto msg = Fmt(args...);
    _error(msg);
  }

  void errorUnexpectedChar();
  void errorUnexpectedToken();

  void expectOperator(StrView s);

  void readString(String& s);
  void readIdentifier(String& s);

  // clang-format off
  const char* cur() const { return _cur;    } 
  StrView source()  const { return _source; }
  size_t line()     const { return _line;   }
  size_t col()      const { return _col;    }
  // clang-format on

protected:
  void _error(StrView msg);

  bool _nextToken();

  bool _parseIdentifier();
  bool _parseNumber();
  bool _parseString();
  void _parseCommentSingleLine();
  void _parseCommentBlock();

  Token _token;
  String _filename;
  StrView _source;

  const char* _cur = nullptr;
  char _ch         = 0;
  size_t _col      = 0;
  size_t _line     = 0;
};

LIBNG_INLINE
String enumStr(ShaderLexer::TokenType type) {
  using E = ShaderLexer::TokenType;
  switch (type) {
    // clang-format off
    case E::None:       return "None";
    case E::Identifier: return "Identifier";
    case E::Number:     return "Number";
    case E::String:     return "String";
    case E::Operator:   return "Operator";
    case E::Newline:    return "Newline";
    // clang-format on
    default: {
      LIBNG_ASSERT(false);
      return "";
    }
  }
}

LIBNG_FORMATTER_ENUM(ShaderLexer::TokenType);
LIBNG_FORMATTER(ShaderLexer::Token);

} // namespace libng