#include <compiler/ShaderLexer.hpp>

namespace libng {

void ShaderLexer::Token::setNone() {
  type = TokenType::None;
  str.clear();
}

void ShaderLexer::Token::onFormat(fmt::format_context& ctx) const {
  // fmt::format_to(ctx.out(), "({}, {})", type, str); // Issue: need to fix
}

} // namespace libng