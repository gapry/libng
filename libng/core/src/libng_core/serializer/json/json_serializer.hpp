#pragma once

#include <libng_core/exception/error.hpp>
#include <libng_core/libcxx/fixed_vector.hpp>
#include <libng_core/libcxx/json.hpp>
#include <libng_core/libcxx/string.hpp>
#include <libng_core/log/log.hpp>
#include <libng_core/serializer/json/json_io.hpp>
#include <libng_core/types/function.hpp>
#include <libng_core/types/noncopyable.hpp>
#include <libng_core/types/number.hpp>

#define LIBNG_NAMED_IO(SE, V) SE.named_io(#V, V)

namespace libng {

struct json_serializer : public NonCopyable {
  using This = json_serializer;

  json_serializer(Json& out_json)
    : _json(out_json) {
    LIBNG_LOG("{}\n", __LIBNG_FUNCTION__);

    _stack.emplace_back(&_json);
  }

  // clang-format off
  void io(u8&  v) { LIBNG_LOG("{}\n", __LIBNG_FUNCTION__); to_value(v); }
  void io(u16& v) { LIBNG_LOG("{}\n", __LIBNG_FUNCTION__); to_value(v); }
  void io(u32& v) { LIBNG_LOG("{}\n", __LIBNG_FUNCTION__); to_value(v); }
  void io(u64& v) { LIBNG_LOG("{}\n", __LIBNG_FUNCTION__); to_value(v); }

  void io(i8&  v) { LIBNG_LOG("{}\n", __LIBNG_FUNCTION__); to_value(v); }
  void io(i16& v) { LIBNG_LOG("{}\n", __LIBNG_FUNCTION__); to_value(v); }
  void io(i32& v) { LIBNG_LOG("{}\n", __LIBNG_FUNCTION__); to_value(v); }
  void io(i64& v) { LIBNG_LOG("{}\n", __LIBNG_FUNCTION__); to_value(v); }
  
  void io(f32&  v) { LIBNG_LOG("{}\n", __LIBNG_FUNCTION__); to_value(v); }
  void io(f64&  v) { LIBNG_LOG("{}\n", __LIBNG_FUNCTION__); to_value(v); }
  void io(f128& v) { LIBNG_LOG("{}\n", __LIBNG_FUNCTION__); to_value(v); }
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
  void to_value(const V& val) {
    LIBNG_LOG("{}, stack size = {}\n", __LIBNG_FUNCTION__, _stack.size());

    auto& current = _stack.back();
    if (!current->is_null()) {
      throw LIBNG_ERROR("It has already contained value.");
    }
    *current = val;
  }

  template<class V>
  void to_enum(const V& val) {
    LIBNG_LOG("{}\n", __LIBNG_FUNCTION__);

    auto data = enumStr(val);
    LIBNG_LOG("enumStr(val) = {}\n", data);

    to_value(data);
  }

  void begin_object() {
    LIBNG_LOG("{}\n", __LIBNG_FUNCTION__);

    auto& current = _stack.back();
    if (!current->is_null()) {
      throw LIBNG_ERROR("{}\n", "serializer:json: begin_object()");
    }
    *current = Json::object();
  }

  void end_object() {
    LIBNG_LOG("{}\n", __LIBNG_FUNCTION__);

    auto& current = _stack.back();
    if (!current->is_object()) {
      throw LIBNG_ERROR("{}\n", "serializer:json: end_object()");
    }
  }

  void to_str_view(StrView val) {
    LIBNG_LOG("{}\n", __LIBNG_FUNCTION__);

    auto& current = _stack.back();
    if (!current->is_null()) {
      throw LIBNG_ERROR("It has already contained value.");
    }
    *current  = "";
    auto* dst = current->get_ptr<Json::string_t*>();
    dst->assign(val.begin(), val.end());
  }

  template<class V>
  void to_object_member(const char* name, V& val) {
    LIBNG_LOG("{}\n", __LIBNG_FUNCTION__);

    auto& obj = _stack.back();
    if (!obj->is_object()) {
      throw LIBNG_ERROR("{}\n", "serializer:json: not found object");
    }
    // std::cout << "obj = " << obj << "\n"; // Log

    auto& member_value = obj->operator[](name); // Issue
    // std::cout << "member_value = " << member_value << "\n";

    _stack.emplace_back(&member_value);
    // std::cout << "_stack " << _stack.back() << "\n"; // Log

    io(val);

    _stack.pop_back(); // Issue
    // std::cout << "_stack " << _stack.back() << "\n"; // Log
  }

  void begin_array() {
    LIBNG_LOG("{}\n", __LIBNG_FUNCTION__);

    auto& current = _stack.back();
    if (!current->is_null()) {
      throw LIBNG_ERROR("{}\n", "serializer:json: it isn't empty");
    }
    *current = Json::array();
  }

  void resize_array(size_t size) {
    LIBNG_LOG("{}\n", __LIBNG_FUNCTION__);

    auto& current = _stack.back();
    if (!current->is_array()) {
      throw LIBNG_ERROR("{}\n", "serializer:json: resize_array");
    }

    auto* json_array = current->get_ptr<Json::array_t*>();
    json_array->resize(size);
  }

  void end_array() {
    LIBNG_LOG("{}\n", __LIBNG_FUNCTION__);

    auto& current = _stack.back();
    if (!current->is_array()) {
      throw LIBNG_ERROR("{}\n", "serializer:json: end_array");
    }
  }

  template<class V>
  void to_array_element(size_t index, V& val) {
    LIBNG_LOG("{}\n", __LIBNG_FUNCTION__);

    auto& current = _stack.back();
    if (!current->is_array()) {
      throw LIBNG_ERROR("{}\n", "serializer:json: to_array_element");
    }

    auto* json_array = current->get_ptr<Json::array_t*>();
    // LIBNG_LOG("index = {}\n", index);
    // LIBNG_LOG("size  = {}\n", json_array->size());

    if (index >= json_array->size()) {
      throw LIBNG_ERROR("{}\n", "serializer:json:array: index overflow");
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
struct json_io<json_serializer, String_<N>> {
  static void io(json_serializer& se, String_<N>& data) {
    LIBNG_LOG("{}\n", __LIBNG_FUNCTION__);

    se.to_str_view(data);
  }
};

template<class T, size_t N>
struct json_io<json_serializer, Vector_<T, N>> {
  static void io(json_serializer& se, Vector_<T, N>& data) {
    LIBNG_LOG("{}\n", __LIBNG_FUNCTION__);

    se.begin_array();
    size_t n = data.size();
    se.resize_array(n);
    for (size_t i = 0; i < n; i++) {
      se.to_array_element(i, data[i]);
    }
    se.end_array();
  }
};

} // namespace libng
