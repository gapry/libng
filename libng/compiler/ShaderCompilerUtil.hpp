#pragma once

#include <libcxx/util/util.hpp>
#include <libcxx/util/UtfUtil.hpp>
#include <exception/error.hpp>
#include <platform/os.hpp>

namespace libng {

enum class ShaderStage
{
  None,
  Vertex,
  Pixel,
};

struct ShaderCompilerUtil {
  ShaderCompilerUtil() = delete;

  static String onGetCurrentDir() {
    String utfPath;

#ifdef LIBNG_OS_WINDOWS
    wchar_t wDir[MAX_PATH + 1];

    if (!::GetCurrentDirectory(MAX_PATH, wDir)) {
      throw LIBNG_ERROR("getCurrentDir");
    }
    utfPath = UtfUtil::toString(wDir);
#endif

    return utfPath;
  }

  static const char* getDxStageProfile(ShaderStage s) {
    switch (s) {
      case ShaderStage::Vertex: return "vs_5_0";
      case ShaderStage::Pixel: return "ps_5_0";
      default: return "";
    }
  }
};

} // namespace libng
