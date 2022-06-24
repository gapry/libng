#pragma once

#include <libng_core/file/JsonFile.hpp>
#include <libng_core/libcxx/string.hpp>
#include <libng_core/libcxx/string_view.hpp>
#include <libng_core/serializer/json/json_serializer.hpp>
#include <libng_core/types/number.hpp>

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
    String name;
    DataType dataType;
    i16 bindPoint = 0;
    i16 bindCount = 0;

    template<class SE>
    void on_json(SE& se) {
      LIBNG_NAMED_IO(se, name);
      LIBNG_NAMED_IO(se, dataType);
      LIBNG_NAMED_IO(se, bindPoint);
      LIBNG_NAMED_IO(se, bindCount);
    };
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