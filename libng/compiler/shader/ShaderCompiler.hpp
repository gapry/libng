#pragma once

#include <app/ConsoleApp.hpp>
#include <app/ProjectSetting.hpp>

#include <file/MemMapFile.hpp>

#include <libcxx/string_view.hpp>
#include <libcxx/span.hpp>

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

  void readFile(ShaderInfo& outInfo, StrView filename);

  void readMem(ShaderInfo& outInfo, ByteSpan data, StrView filename);

  virtual void onRun() override;

private:
  ShaderLexer* lexer          = nullptr;
  ShaderParser* parser        = nullptr;
  ShaderSemantic* typeChecker = nullptr;
  ShaderCodeGen* codeGen      = nullptr;

  MemMapFile _memMapfile;
  ShaderInfo* _outInfo = nullptr;

  String _file;
  String _path;
  ProjectSettings* _proj = nullptr;
};

} // namespace libng