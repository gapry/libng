#pragma once

#include <libng_core/file/JsonFile.hpp>
#include <libng_core/libcxx/string.hpp>
#include <libng_core/libcxx/string_view.hpp>

#include <libng_render/material/ShaderStageMask.hpp>
#include <libng_render/type/RenderDataType.hpp>

namespace libng {

class ShaderStageInfo {
public:
  using DataType = RenderDataType;

  void loadFile(StrView filename_) {
    filename = filename_;
    JsonFile::read(filename_, *this);
  }

  String filename;
  String profile;
  ShaderStageMask stage = ShaderStageMask::None;

  class Param {
  public:
  };

  class Input {
  public:
  };

  class Variable {
  public:
  };

  class ConstBuffer {
  public:
  };

  template<class SE>
  void on_json(SE& se) {
  }
};

} // namespace libng