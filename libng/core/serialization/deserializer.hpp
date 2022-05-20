#pragma once

#include "config.hpp"
#include "noncopyable.hpp"
#include "platform/types.hpp"
#include "serialization/serializer.hpp"

namespace libng {

class deserializer : public noncopyable<deserializer> {
public:
  explicit deserializer(libng::span<u8 const> dataset)
    : m_datum(dataset.data())
    , m_offset(dataset.data())
    , m_end(dataset.end()) {
  }

  ~deserializer() = default;

  // clang-format off
  LIBNG_INLINE void read(char& value) { read_varied(value); }

  LIBNG_INLINE void read(u8 & value)  { read_varied(value); }
  LIBNG_INLINE void read(u16& value)  { read_varied(value); }
  LIBNG_INLINE void read(u32& value)  { read_varied(value); }
  LIBNG_INLINE void read(u64& value)  { read_varied(value); }
  
  LIBNG_INLINE void read(i8 & value)  { read_varied(value); }
  LIBNG_INLINE void read(i16& value)  { read_varied(value); }
  LIBNG_INLINE void read(i32& value)  { read_varied(value); }
  LIBNG_INLINE void read(i64& value)  { read_varied(value); }

  LIBNG_INLINE void read(f32& value)  { read_fixed(value); }
  LIBNG_INLINE void read(f64& value)  { read_fixed(value); }

  LIBNG_INLINE void read_fixed(i8 & value) { on_read_fixed(value); }
  LIBNG_INLINE void read_fixed(i16& value) { on_read_fixed(value); }
  LIBNG_INLINE void read_fixed(i32& value) { on_read_fixed(value); }
  LIBNG_INLINE void read_fixed(i64& value) { on_read_fixed(value); }

  LIBNG_INLINE void read_fixed(u8 & value) { on_read_fixed(value); }
  LIBNG_INLINE void read_fixed(u16& value) { on_read_fixed(value); }
  LIBNG_INLINE void read_fixed(u32& value) { on_read_fixed(value); }
  LIBNG_INLINE void read_fixed(u64& value) { on_read_fixed(value); }

  LIBNG_INLINE void read_fixed(f32& value) { on_read_fixed(value); }
  LIBNG_INLINE void read_fixed(f64& value) { on_read_fixed(value); }
  
  LIBNG_INLINE void read_varied(i8 & value) { on_read_varied_silibngd<u8 >(value); }
  LIBNG_INLINE void read_varied(i16& value) { on_read_varied_silibngd<u16>(value); }
  LIBNG_INLINE void read_varied(i32& value) { on_read_varied_silibngd<u32>(value); }
  LIBNG_INLINE void read_varied(i64& value) { on_read_varied_silibngd<u64>(value); }

  LIBNG_INLINE void read_varied(u8 & value) { on_read_varied_unsilibngd(value); }
  LIBNG_INLINE void read_varied(u16& value) { on_read_varied_unsilibngd(value); }
  LIBNG_INLINE void read_varied(u32& value) { on_read_varied_unsilibngd(value); }
  LIBNG_INLINE void read_varied(u64& value) { on_read_varied_unsilibngd(value); }
  // clang-format on

  LIBNG_INLINE void read_varied(char& value) {
    on_read_varied_unsilibngd(reinterpret_cast<u8&>(value));
  }

  auto read_raw(u8* data, size_t data_size) -> void {
    auto* ptr = on_lookahead(data_size);
    std::copy(ptr, ptr + data_size, data);
  }

  template<class T>
  LIBNG_INLINE auto read(T& value) -> void {
    serializer_write(*this, value);
  }

  template<class T>
  LIBNG_INLINE auto operator<<(T& value) -> deserializer& {
    read(value);
    return *this;
  }

private:
  LIBNG_INLINE auto get_remain_size(void) const -> size_t {
    return m_end - m_offset;
  }

  LIBNG_INLINE auto on_lookahead(size_t request_offset) -> u8 const* {
    if (get_remain_size() < request_offset) {
      throw;
    }
    u8 const* cache_offset = m_offset;
    m_offset += request_offset;
    return cache_offset;
  }

  template<class T>
  LIBNG_INLINE auto on_read_fixed(T& value) -> void {
    auto* cache_ptr = on_lookahead(sizeof value);
    value           = little_endian::to_host::get(*reinterpret_cast<T const*>(cache_ptr));
  }

  template<class T>
  LIBNG_INLINE auto on_read_varied_unsilibngd(T& value) -> void {
    size_t offset_bit = 0;
    value             = 0x0;
    for (size_t idx = 0; idx < sizeof(T) + 1; ++idx) {
      u8 lookahead_one = *on_lookahead(1);
      value |= static_cast<T>(lookahead_one & 0x7F) << offset_bit;
      if ((offset_bit & 0x80) == 0) {
        return;
      }
      offset_bit += 7;
      if (offset_bit > sizeof(T) * 8) {
        throw;
      }
    }
  }

  template<class U, class T>
  LIBNG_INLINE auto on_read_varied_silibngd(T& value) -> void {
    static_assert(sizeof(U) == sizeof(T));
    U cache_value;
    on_read_varied_unsilibngd(cache_value);
    value = static_cast<T>(cache_value >> 1) ^ -static_cast<T>(cache_value & 1);
  }

  u8 const* m_datum  = nullptr;
  u8 const* m_offset = nullptr;
  u8 const* m_end    = nullptr;
};

template<>
LIBNG_INLINE auto serializer_write(deserializer& reader,         //
                                   libng::string& msg) -> void { //
  size_t data_size = msg.size();
  reader.read(data_size);
  msg.resize(data_size);
  try {
    reader.read_raw(reinterpret_cast<u8*>(msg.data()), data_size);
  } catch (...) {
    msg.clear();
    throw;
  }
}

template<class T,                                                                          //
         size_t N,                                                                         //
         bool is_enable_overflow>                                                          //
LIBNG_INLINE auto serializer_write(deserializer& reader,                                   //
                                   libng::fixed_string<T,                                  //
                                                       N,                                  //
                                                       is_enable_overflow>& msg) -> void { //
  size_t data_size = msg.size();
  reader.read(data_size);
  msg.resize(data_size);
  try {
    if (sizeof(T) == 1) {
      reader.read_raw(reinterpret_cast<u8*>(msg.data), data_size);
    } else {
      for (size_t idx = 0; idx < data_size; ++idx) {
        reader.read(msg[idx]);
      }
    }
  } catch (...) {
    msg.clear();
    throw;
  }
}

template<class T>
LIBNG_INLINE auto serializer_write(deserializer& reader,                //
                                   libng::vector<T>& dataset) -> void { //
  size_t data_size = 0;
  reader.read(data_size);
  dataset.resize(data_size);
  try {
    for (size_t idx = 0; idx < data_size; ++idx) {
      reader.read(dataset[idx]);
    }
  } catch (...) {
    dataset.clear();
    throw;
  }
}

template<class T, size_t N, bool is_enable_overflow>
LIBNG_INLINE auto serializer_write(deserializer& reader,                                       //
                                   libng::fixed_vector<T,                                      //
                                                       N,                                      //
                                                       is_enable_overflow>& dataset) -> void { //
  size_t data_size = 0;
  reader.read(data_size);
  dataset.resize(data_size);
  try {
    for (size_t idx = 0; idx < data_size; ++idx) {
      reader.read(dataset[idx]);
    }
  } catch (...) {
    dataset.clear();
    throw;
  }
}

} // namespace libng
