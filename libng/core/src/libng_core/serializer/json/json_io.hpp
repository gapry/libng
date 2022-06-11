#pragma once

#include <type_traits>

namespace libng {

template<class SE, class T, class ENABLE = void> // Issue
struct json_io {
  static void io(SE& se, T& data) {
  }
};

template<class SE, class T>
struct json_io<SE, T, std::enable_if_t<std::is_enum_v<T>>> { // Issue
  static void io(SE& se, T& data) {
  }
};

} // namespace libng