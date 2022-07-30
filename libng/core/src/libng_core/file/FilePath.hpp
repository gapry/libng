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

  static void SetAssetsPath(const char* const path);

  static String GetTestDataPath(const char* const name);

  static StrView DirName(StrView path);

  static bool IsRealPath(const StrView& path);

  static String RealPath(StrView path);

  static StrView extension(StrView path);

  static String _path;
};

} // namespace libng
