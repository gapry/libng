#include <compiler/shader/ShaderLexer.hpp>

namespace libng {

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