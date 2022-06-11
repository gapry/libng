#pragma once

#include <libng_core/app/ConsoleApp.hpp>
#include <libng_core/app/ProjectSetting.hpp>
#include <libng_core/file/MemMapFile.hpp>
#include <libng_core/libcxx/string_view.hpp>
#include <libng_core/libcxx/span.hpp>
#include <libng_render/material/ShaderInfo.hpp>
#include <libng_compiler/shader/ShaderLexer.hpp>
#include <libng_compiler/shader/ShaderParser.hpp>
#include <libng_compiler/shader/ShaderSemantic.hpp>
#include <libng_compiler/shader/ShaderCodeGen.hpp>

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