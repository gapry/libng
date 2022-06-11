#pragma once

#include <libng_core/libcxx/util/util.hpp>
#include <libng_core/libcxx/string.hpp>

namespace libng {

struct FilePath {
  static String getDir(StrView path) {
    auto* end   = path.end();
    auto* begin = path.begin();

    if (end == nullptr) {
      return String();
    }

    auto* p = end - 1;

    for (; p >= begin; p--) {
      if (*p == '/' || *p == '\\') {
        return String(begin, p);
      }
    }
    return String();
  }

  static StrView FilePath::dirname(StrView path) {
    auto* end   = path.end();
    auto* begin = path.begin();

    if (end == nullptr)
      return StrView();

    auto* p = end - 1;
    for (; p >= begin; p--) {
      if (*p == '/' || *p == '\\') {
        return StrView(begin, p - begin);
      }
    }
    return StrView();
  }
};

} // namespace libng
