#pragma once

#include <libng_core/libcxx/string.hpp>
#include <libng_core/libcxx/string_view.hpp>
#include <libng_render/material/ShaderStageMask.hpp>
#include <libng_render/material/ShaderUtil.hpp>

namespace libng {

class ShaderCodeGen {
public:
  ShaderCodeGen();
  ~ShaderCodeGen();

private:
  void resetApi();

  String _apiType;
};

} // namespace libng
