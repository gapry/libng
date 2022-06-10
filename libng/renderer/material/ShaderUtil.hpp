#pragma once

#include <libcxx/util/util.hpp>
#include <encoding/UtfUtil.hpp>
#include <exception/error.hpp>
#include <platform/os.hpp>
#include <platform/graphics.hpp>
#include <renderer/material/ShaderStage.hpp>
#include <renderer/backend/dx11/DX11Util.hpp>

namespace libng {

struct ShaderUtil {
  ShaderUtil() = delete;

  static const char* getStageProfile(ShaderStage s) {
#if LIBNG_RENDER_DX11
    return DX11Util::getDxStageProfile(s);
#else
    return "Unknown Stage Profile";
#endif
  }
};

} // namespace libng
