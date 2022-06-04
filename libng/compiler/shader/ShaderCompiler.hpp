#pragma once

#include <app/ConsoleApp.hpp>
#include <app/ProjectSetting.hpp>

#include <file/MemMapFile.hpp>

#include <renderer/material/ShaderInfo.hpp>

#include <compiler/shader/ShaderLexer.hpp>
#include <compiler/shader/ShaderParser.hpp>
#include <compiler/shader/ShaderSemantic.hpp>
#include <compiler/shader/ShaderCodeGen.hpp>

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

  MemMapFile _memMapfile;
  ShaderInfo* _outInfo = nullptr;

  String _file;
  String _path;
  ProjectSettings* _proj = nullptr;
};

} // namespace libng