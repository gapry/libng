#pragma once

#include <libng_core/libcxx/json.hpp>
#include <libng_core/libcxx/fixed_vector.hpp>
#include <libng_core/libcxx/string.hpp>
#include <libng_core/libcxx/string_view.hpp>
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

  template<class V>
  void named_io(const char* name, V& val) {
    LIBNG_LOG("{}\n", __LIBNG_FUNCTION__);
    to_object_member(name, val);
  }

  template<class SE, class T, class ENABLE>
  friend struct json_io;

protected:
  template<class V>
  void to_value(V& val) {
    LIBNG_LOG("{}\n", __LIBNG_FUNCTION__);

    auto& current = _stack.back();
    if (current->is_null()) {
      throw LIBNG_ERROR("json deserializer:to_value val is null");
    }
    val = *current;
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

  StrView to_str_view() {
    LIBNG_LOG("{}\n", __LIBNG_FUNCTION__);

    auto& current = _stack.back();
    if (!current->is_string()) {
      throw LIBNG_ERROR("{}\n", "deserializer:json: to_str_view");
    }
    auto* str = current->get_ptr<Json::string_t*>();
    return StrView(str->data(), str->size());
  }

  template<class V>
  void to_object_member(const char* name, V& val) {
    LIBNG_LOG("{}\n", __LIBNG_FUNCTION__);

    auto& current = _stack.back();
    // std::cout << *current << std::endl;

    if (!current->is_object()) {
      throw LIBNG_ERROR("{}\n", "deserializer:json: to_object_member");
    }
    auto& member_value = current->operator[](name);
    _stack.emplace_back(&member_value);
    io(val);
    _stack.pop_back();
  }

  size_t begin_array() {
    LIBNG_LOG("{}\n", __LIBNG_FUNCTION__);

    auto& current = _stack.back();
    if (!current->is_array()) {
      throw LIBNG_ERROR("{}\n", "deserializer:json: begin_array");
    }

    auto* json_array = current->get_ptr<Json::array_t*>();
    return json_array->size();
  }

  void end_array() {
    LIBNG_LOG("{}\n", __LIBNG_FUNCTION__);

    auto& current = _stack.back();
    if (!current->is_array()) {
      throw LIBNG_ERROR("{}\n", "deserializer:json: end_array");
    }
  }

  template<class V>
  void to_array_element(size_t index, V& val) {
    LIBNG_LOG("{}\n", __LIBNG_FUNCTION__);

    auto& current = _stack.back();
    if (!current->is_array()) {
      throw LIBNG_ERROR("{}\n", "deserializer:json: to_array_element");
    }

    auto* json_array = current->get_ptr<Json::array_t*>();
    if (index >= json_array->size()) {
      throw LIBNG_ERROR("{}\n", "deserializer:json: to_array_element");
    }

    auto& elem_val = json_array->at(index);
    _stack.emplace_back(&elem_val);
    io(val);
    _stack.pop_back();
  }

private:
  Json& _json;
  Vector_<Json*, (16 << 1) + (16 >> 1)> _stack;
};

template<size_t N>
struct json_io<json_deserializer, String_<N>> {
  static void io(json_deserializer& se, String_<N>& data) {
    LIBNG_LOG("{}\n", __LIBNG_FUNCTION__);

    data = se.to_str_view();
  }
};

template<class T, size_t N>
struct json_io<json_deserializer, Vector_<T, N>> {
  static void io(json_deserializer& se, Vector_<T, N>& data) {
    LIBNG_LOG("{}\n", __LIBNG_FUNCTION__);

    size_t n = se.begin_array();
    data.clear();
    data.resize(n);
    for (size_t i = 0; i < n; ++i) {
      se.to_array_element(i, data[i]);
    }
    se.end_array();
  }
};

} // namespace libng