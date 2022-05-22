#pragma once

#include <libcxx/util/util.hpp>
#include <libcxx/util/UtfUtil.hpp>
#include <exception/error.hpp>
#include <platform/os.hpp>

namespace libng {

struct ShaderCompilerUtil {
  ShaderCompilerUtil() = delete;

  static String onGetCurrentDir() {
    String utfPath;

#ifdef LIBNG_OS_WINDOWS
    wchar_t wDir[MAX_PATH + 1];

    if (!::GetCurrentDirectory(MAX_PATH, wDir)) {
      throw LIBNG_ERROR("getCurrentDir");
    }
    String utfPath = UtfUtil::toString(wDir);
#endif

    return utfPath;
  }
};

} // namespace libng
