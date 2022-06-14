#pragma once

#include <libng_core/libcxx/json.hpp>
#include <libng_core/libcxx/fixed_vector.hpp>
#include <libng_core/log/log.hpp>
#include <libng_core/exception/error.hpp>
#include <libng_core/types/number.hpp>
#include <libng_core/types/noncopyable.hpp>
#include <libng_core/serializer/json/json_serializer.hpp>

namespace libng {

class json_deserializer : public NonCopyable {
  using This = json_deserializer;

public:
  json_deserializer(Json& json)
    : _json(json) {
    _stack.emplace_back(&_json);
    LIBNG_LOG("{}\n", __LIBNG_FUNCTION__);
  }

  // clang-format off
  void io(u8&  v) { to_value(v); LIBNG_LOG("{}\n", __LIBNG_FUNCTION__); }
  void io(u16& v) { to_value(v); LIBNG_LOG("{}\n", __LIBNG_FUNCTION__); }
  void io(u32& v) { to_value(v); LIBNG_LOG("{}\n", __LIBNG_FUNCTION__); }
  void io(u64& v) { to_value(v); LIBNG_LOG("{}\n", __LIBNG_FUNCTION__); }

  void io(i8&  v) { to_value(v); }
  void io(i16& v) { to_value(v); }
  void io(i32& v) { to_value(v); }
  void io(i64& v) { to_value(v); }
  
  void io(f32&  v) { to_value(v); }
  void io(f64&  v) { to_value(v); }
  void io(f128& v) { to_value(v); }
  // clang-format on

  template<class V>
  void io(V& val) {
    LIBNG_LOG("{}\n", __LIBNG_FUNCTION__);
    json_io<This, V>::io(*this, val);
  }

  template<class SE, class T, class ENABLE>
  friend struct json_io;

protected:
  template<class V>
  void to_value(V& val) {
    auto& current = _stack.back();
    if (current->is_null()) {
      throw LIBNG_ERROR("json deserializer:to_value val is null");
    }
    val = *current;
    LIBNG_LOG("{}\n", __LIBNG_FUNCTION__);
  }

  void begin_object() {
    LIBNG_LOG("{}\n", __LIBNG_FUNCTION__);

    auto& current = _stack.back();
    if (!current->is_object()) {
      throw LIBNG_ERROR("{}\n", "deserializer:json: begin_object()");
    }
  }

  void end_object() {
    LIBNG_LOG("{}\n", __LIBNG_FUNCTION__);

    auto& current = _stack.back();
    if (!current->is_object()) {
      throw LIBNG_ERROR("{}\n", "deserializer:json: begin_object()");
    }
  }

private:
  Json& _json;
  Vector_<Json*, (16 << 1) + (16 >> 1)> _stack;
};

} // namespace libng