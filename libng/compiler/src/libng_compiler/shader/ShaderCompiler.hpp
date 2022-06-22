#pragma once

#include <libng_core/app/ConsoleApp.hpp>
#include <libng_core/app/ProjectSetting.hpp>
#include <libng_core/file/MemMapFile.hpp>
#include <libng_core/libcxx/span.hpp>
#include <libng_core/libcxx/string_view.hpp>
#include <libng_core/libcxx/unique_ptr.hpp>
#include <libng_core/memory/ComPtr.hpp>
#include <libng_render/material/ShaderInfo.hpp>

namespace libng {

class ShaderCompiler : public ConsoleApp {
public:
  ShaderCompiler();
  ~ShaderCompiler();

  virtual void onRun(int argc, char** argv) override;

private:
  String _apiType;
};

} // namespace libng