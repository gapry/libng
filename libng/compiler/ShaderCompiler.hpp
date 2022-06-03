#pragma once

#include <app/ConsoleApp.hpp>
#include <app/ProjectSetting.hpp>

#include <compiler/ShaderLexer.hpp>
#include <compiler/ShaderParser.hpp>
#include <compiler/ShaderSemantic.hpp>
#include <compiler/ShaderCodeGen.hpp>

namespace libng {

class ShaderCompiler : public ConsoleApp {
public:
  ShaderCompiler();

  ~ShaderCompiler();

  virtual void onRun() override;

private:
  ShaderLexer* lexer          = nullptr;
  ShaderParser* parser        = nullptr;
  ShaderSemantic* typeChecker = nullptr;
  ShaderCodeGen* codeGer      = nullptr;

  String _file;
  String _path;
  ProjectSettings* _proj = nullptr;
};

} // namespace libng