#pragma once

#include <libcxx/util/util.hpp>
#include <libcxx/util/UtfUtil.hpp>
#include <exception/error.hpp>
#include <platform/os.hpp>

namespace libng {

namespace shader {

String onGetCurrentDir() {
  wchar_t wDir[MAX_PATH + 1];

  if (!::GetCurrentDirectory(MAX_PATH, wDir)) {
    throw LIBNG_ERROR("getCurrentDir");
  }

  String utfPath = UtfUtil::toString(wDir);
  return utfPath;
}

} // namespace shader

} // namespace libng
