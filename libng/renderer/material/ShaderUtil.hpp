#pragma once

#include <libcxx/util/util.hpp>
#include <encoding/UtfUtil.hpp>
#include <exception/error.hpp>
#include <platform/os.hpp>
#include <renderer/material/ShaderStage.hpp>

namespace libng {

struct ShaderUtil {
  ShaderUtil() = delete;

  static const char* getDxStageProfile(ShaderStage s) {
    switch (s) {
      case ShaderStage::Vertex: return "vs_5_0";
      case ShaderStage::Pixel: return "ps_5_0";
      default: return "";
    }
  }
};

} // namespace libng
