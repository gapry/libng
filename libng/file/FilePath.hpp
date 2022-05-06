#pragma once

#include <libcxx/util.hpp>
#include <libcxx/string.hpp>

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
};

} // namespace libng