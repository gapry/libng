#pragma once

#include <libng_core/file/Directory.hpp>
#include <libng_core/libcxx/string.hpp>
#include <libng_core/libcxx/string_view.hpp>
#include <libng_core/libcxx/util/StringUtil.hpp>

namespace libng {

struct FilePath {
  FilePath() = delete;

  static String GetSlash();

  static String GetAssetsPath();

  static StrView DirName(StrView path);

  static bool IsRealPath(const StrView& path);

  static String RealPath(StrView path);
};

} // namespace libng
