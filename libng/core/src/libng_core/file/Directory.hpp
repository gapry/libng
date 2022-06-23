#pragma once

#include <libng_core/encoding/UtfUtil.hpp>
#include <libng_core/exception/error.hpp>
#include <libng_core/file/FilePath.hpp>
#include <libng_core/libcxx/string.hpp>
#include <libng_core/libcxx/string_view.hpp>
#include <libng_core/platform/os.hpp>

namespace libng {

struct Directory {
  Directory() = delete;

  static void setCurrent(StrView dir);
  static String getCurrent();

  static void create(StrView path);
  static bool exists(StrView path);

private:
  static void _create(StrView path);
};

} // namespace libng