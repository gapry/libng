#pragma once

#include <libng_core/exception/error.hpp>
#include <libng_core/log/log.hpp>
#include <libng_core/types/function.hpp>
#include <libng_core/types/number.hpp>
#include <libng_core/types/noncopyable.hpp>
#include <libng_core/libcxx/json.hpp>
#include <libng_core/libcxx/fixed_vector.hpp>
#include <libng_core/serializer/json/json_io.hpp>

#define SGE_NAMED_IO(SE, V) SE.named_io(#V, V)

namespace libng {

struct json_serializer : public NonCopyable {
  using This = json_serializer;

  json_serializer(Json& out_json)
    : _json(out_json) {
    _stack.emplace_back(&_json);
    LIBNG_LOG("{}\n", __LIBNG_FUNCTION__);
  }

  // clang-format off
  void io(u8& v)  { to_value(v); LIBNG_LOG("{}\n", __LIBNG_FUNCTION__); }
  void io(u16& v) { to_value(v); LIBNG_LOG("{}\n", __LIBNG_FUNCTION__); }
  void io(u32& v) { to_value(v); LIBNG_LOG("{}\n", __LIBNG_FUNCTION__); }
  void io(u64& v) { to_value(v); LIBNG_LOG("{}\n", __LIBNG_FUNCTION__); }
  // clang-format on

protected:
  template<class V>
  void to_value(const V& val) {
    LIBNG_LOG("{}, stack size = {}\n", __LIBNG_FUNCTION__, _stack.size());
    auto& current = _stack.back();
    if(!current->is_null()) {
      throw LIBNG_ERROR("It has already contained value.");
    }
    *current = val;
    LIBNG_LOG("{}\n", __LIBNG_FUNCTION__);
  }

private:
  Json& _json;
  Vector_<Json*, (16 << 1) + (16 >> 1)> _stack;
};

} // namespace libng
