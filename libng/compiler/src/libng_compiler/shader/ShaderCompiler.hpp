#pragma once

#include <libng_core/app/ConsoleApp.hpp>
#include <libng_core/app/ProjectSetting.hpp>
#include <libng_core/file/MemMapFile.hpp>
#include <libng_core/libcxx/string_view.hpp>
#include <libng_core/libcxx/span.hpp>
#include <libng_core/libcxx/unique_ptr.hpp>
#include <libng_core/memory/ComPtr.hpp>
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

  virtual void onRun(int argc, char** argv) override;

private:
  UPtr<ShaderLexer> lexer;
  UPtr<ShaderParser> parser;
  UPtr<ShaderSemantic> typeChecker;
  UPtr<ShaderCodeGen> codeGen;
  UPtr<ShaderInfo> _outInfo;
  
  ProjectSettings* _proj = nullptr; // Issue: UPtr to static variable.

  MemMapFile _memMapfile;
  String _file;
  String _path;
  String _apiType;
  String _assetsPath;
};

} // namespace libng