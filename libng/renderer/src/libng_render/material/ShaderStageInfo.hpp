#pragma once

#include <libng_core/file/JsonFile.hpp>
#include <libng_core/libcxx/fixed_vector.hpp>
#include <libng_core/libcxx/string.hpp>
#include <libng_core/libcxx/string_view.hpp>
#include <libng_core/serializer/json/json_serializer.hpp>
#include <libng_core/types/number.hpp>

#include <libng_render/material/ShaderStageMask.hpp>
#include <libng_render/type/RenderDataType.hpp>
#include <libng_render/vertex/VertexSemantic.hpp>

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
    String name;
    VertexSemantic semantic = VertexSemantic::None;
    RenderDataType dataType = RenderDataType::None;

    template<class SE>
    void on_json(SE& se) {
      LIBNG_NAMED_IO(se, name);
      LIBNG_NAMED_IO(se, semantic);
      LIBNG_NAMED_IO(se, dataType);
    }
  };

  class Variable {
  public:
    String name;
    size_t offset     = 0;
    DataType dataType = DataType::None;
    bool rowMajor     = true;

    template<class SE>
    void on_json(SE& se) {
      LIBNG_NAMED_IO(se, name);
      LIBNG_NAMED_IO(se, offset);
      LIBNG_NAMED_IO(se, dataType);
    }
  };

  class ConstBuffer {
  public:
    String name;
    i16 bindPoint   = 0;
    i16 bindCount   = 0;
    size_t dataSize = 0;
    Vector_<Variable, 4> variables;

    template<class SE>
    void on_json(SE& se) {
      LIBNG_NAMED_IO(se, name);
      LIBNG_NAMED_IO(se, bindPoint);
      LIBNG_NAMED_IO(se, bindCount);
      LIBNG_NAMED_IO(se, dataSize);
      LIBNG_NAMED_IO(se, variables);
    }

    const Variable* findVariable(StrView propName) const {
      for (auto& v : variables) {
        if (v.name == propName) {
          return &v;
        }
      }
      return nullptr;
    }
  };

  Vector_<Input, 8> inputs;
  Vector_<Param, 8> params;
  Vector_<ConstBuffer, 4> constBuffers;

  class Texture {
  public:
    String name;
    i16 bindPoint     = 0;
    i16 bindCount     = 0;
    DataType dataType = DataType::None;

    template<class SE>
    void on_json(SE& se) {
      LIBNG_NAMED_IO(se, name);
      LIBNG_NAMED_IO(se, bindPoint);
      LIBNG_NAMED_IO(se, bindCount);
      LIBNG_NAMED_IO(se, dataType);
    }
  };
  Vector_<Texture, 8> textures;

  template<class SE>
  void on_json(SE& se) {
  }
};

} // namespace libng