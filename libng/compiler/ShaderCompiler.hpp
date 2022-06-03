#pragma once

#include <app/ConsoleApp.hpp>

#include <compiler/ShaderLexer.hpp>
#include <compiler/ShaderParser.hpp>
#include <compiler/ShaderSemantic.hpp>
#include <compiler/ShaderCodeGen.hpp>

namespace libng {

class ShaderCompiler : public ConsoleApp {
public:
  virtual void onRun() override;

private:
  ShaderLexer* lexer          = nullptr;
  ShaderParser* parser        = nullptr;
  ShaderSemantic* typeChecker = nullptr;
  ShaderCodeGen* codeGer      = nullptr;
};

} // namespace libng