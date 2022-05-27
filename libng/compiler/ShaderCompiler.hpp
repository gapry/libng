#pragma once

#include <compiler/ShaderLexer.hpp>
#include <compiler/ShaderParser.hpp>
#include <compiler/ShaderSemantic.hpp>
#include <compiler/ShaderCodeGen.hpp>

namespace libng {

class ShaderCompiler {
public:
  void execute(const String& filename);

private:
  ShaderLexer* lexer;
  ShaderParser* parser;
  ShaderSemantic* typeChecker;
  ShaderCodeGen* codeGen;
};

} // namespace libng