#pragma once

#include <libng_core/types/function.hpp>
#include <type_traits>

namespace libng {

template<class SE, class T, class ENABLE = void>
struct json_io {
  static void io(SE& se, T& data) {
    // LIBNG_LOG("{}\n", __LIBNG_FUNCTION__);

    se.begin_object();
    data.on_json(se);
    se.end_object();
  }
};

template<class SE, class T>
struct json_io<SE, T, std::enable_if_t<std::is_enum_v<T>>> {
  static void io(SE& se, T& data) {
    // LIBNG_LOG("{}\n", __LIBNG_FUNCTION__);

    se.to_enum(data);
  }
};

} // namespace libng