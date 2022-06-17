#pragma once

#include <libng_core/encoding/UtfUtil.hpp>
#include <libng_core/exception/error.hpp>
#include <libng_core/platform/os.hpp>
#include <libng_core/platform/graphics.hpp>
#include <libng_render/material/ShaderStage.hpp>
#include <libng_render/backend/dx11/DX11Util.hpp>

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
