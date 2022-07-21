#pragma once

#include <libng_render/backend/dx11/Util_DX11.hpp>
#include <libng_render/material/ShaderStageMask.hpp>

namespace libng {

struct ShaderUtil {
  ShaderUtil() = delete;

  static const char* getStageProfile(ShaderStageMask s) {
#if LIBNG_RENDER_DX11
    return Util_DX11::getDxStageProfile(s);
#else
    return "Unknown Stage Profile";
#endif
  }
};

} // namespace libng
