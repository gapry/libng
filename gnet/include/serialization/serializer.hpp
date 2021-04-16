#pragma once

#include "config.hpp"
#include "platform/compiler.hpp"
#include "platform/endian.hpp"
#include "platform/types.hpp"

namespace gnet {

template<class S, class T>
GNET_INLINE auto serializer_write(S& writer, T& value) -> void {
  value.write(writer);
}

class serializer : public noncopyable<serializer> {
public:
  explicit serializer(gnet::vector<u8>& buff)
    : m_buff(&buff) {
  }

  ~serializer() noexcept = default;

  // clang-format off
  GNET_INLINE void write(i8 & value)  { write_varied(value); }
  GNET_INLINE void write(i16& value)  { write_varied(value); }
  GNET_INLINE void write(i32& value)  { write_varied(value); }
  GNET_INLINE void write(i64& value)  { write_varied(value); }

  GNET_INLINE void write(u8 & value)  { write_varied(value); }
  GNET_INLINE void write(u16& value)  { write_varied(value); }
  GNET_INLINE void write(u32& value)  { write_varied(value); }
  GNET_INLINE void write(u64& value)  { write_varied(value); }
  
  GNET_INLINE void write(f32& value)  { write_fixed(value); }
  GNET_INLINE void write(f64& value)  { write_fixed(value); }

  GNET_INLINE void write(char& value) { write_varied(value); }

  GNET_INLINE void write_fixed(u8 & value) { on_write_fixed(value); }
  GNET_INLINE void write_fixed(u16& value) { on_write_fixed(value); }
  GNET_INLINE void write_fixed(u32& value) { on_write_fixed(value); }
  GNET_INLINE void write_fixed(u64& value) { on_write_fixed(value); }
  
  GNET_INLINE void write_fixed(i8 & value) { on_write_fixed(value); }
  GNET_INLINE void write_fixed(i16& value) { on_write_fixed(value); }
  GNET_INLINE void write_fixed(i32& value) { on_write_fixed(value); }
  GNET_INLINE void write_fixed(i64& value) { on_write_fixed(value); }

  GNET_INLINE void write_fixed(f32& value) { on_write_fixed(value); }
  GNET_INLINE void write_fixed(f64& value) { on_write_fixed(value); }

  GNET_INLINE void write_varied(i8 & value) { on_write_varied_signed<u8 >(value); }
  GNET_INLINE void write_varied(i16& value) { on_write_varied_signed<u16>(value); }
  GNET_INLINE void write_varied(i32& value) { on_write_varied_signed<u32>(value); }
  GNET_INLINE void write_varied(i64& value) { on_write_varied_signed<u64>(value); }

  GNET_INLINE void write_varied(u8 & value) { on_write_varied_unsigned(value); }
  GNET_INLINE void write_varied(u16& value) { on_write_varied_unsigned(value); }
  GNET_INLINE void write_varied(u32& value) { on_write_varied_unsigned(value); }
  GNET_INLINE void write_varied(u64& value) { on_write_varied_unsigned(value); }
  // clang-format on

  GNET_INLINE void write_varied(char& value) {
    on_write_varied_unsigned(reinterpret_cast<u8&>(value));
  }

  auto write_raw(u8 const* data,             //
                 size_t data_size) -> void { //
    m_buff->reserve(m_buff->size() + data_size);
    m_buff->insert(m_buff->end(), data, data + data_size);
  }

  template<class T>
  GNET_INLINE auto write(T& value) -> void {
    serializer_write(*this, value);
  }

  template<class T>
  GNET_INLINE auto operator<<(T& value) -> serializer {
    write(value);
    return *this;
  }

private:
  GNET_INLINE auto on_lookahead(size_t request_size) -> u8* {
    size_t old_size = m_buff->size();
    m_buff->resize(old_size + request_size);
    return m_buff->data() + old_size;
  }

  template<class T>
  GNET_INLINE auto on_write_fixed(T& value) -> void {
    auto* cache_ptr                  = on_lookahead(sizeof value);
    *reinterpret_cast<T*>(cache_ptr) = little_endian::from_host::get(value);
  }

  template<class T>
  GNET_INLINE auto on_write_varied_unsigned(T& value) -> void {
    T cache = value;
    for (size_t idx = 0; idx < sizeof(T) + 1; idx++) {
      u8 msb = cache >= 0x80 ? 0x80 : 0x0;
      m_buff->push_back(static_cast<u8>(cache) | msb);
      cache >>= 7;
      if (0 == cache) {
        return;
      }
    }
    // throw
  }

  template<class U, class T>
  GNET_INLINE auto on_write_varied_signed(T& value) -> void {
    static_assert(sizeof(U) == sizeof(T));
    U cache = static_cast<U>((value << 1) ^ (value >> (sizeof(T) * 8 - 1)));
    on_write_varied_unsigned(cache);
  }

  vector<u8>* m_buff = nullptr;
};

template<>
GNET_INLINE auto serializer_write(serializer& writer,    //
                                  string& msg) -> void { //
  size_t data_size = msg.size();
  writer.write(data_size);
  writer.write_raw(reinterpret_cast<u8 const*>(msg.data()), data_size);
}

template<class T,                                                       //
         size_t N,                                                      //
         bool is_enable_overflow>                                       //
GNET_INLINE auto serializer_write(serializer& writer,                   //
                                  gnet::fixed_string<T,                 //
                                                     N,                 //
                                                     is_enable_overflow //
                                                     >& msg) -> void {  //
  size_t data_size = msg.size();
  writer.write(data_size);
  if (sizeof(T) == 1) {
    writer.write_raw(reinterpret_cast<u8 const*>(msg.data()), data_size);
  } else {
    for (size_t idx = 0; idx < data_size; ++idx) {
      writer.write(msg[idx]);
    }
  }
}

template<class T>
GNET_INLINE auto serializer_write(serializer& writer,                 //
                                  gnet::vector<T>& dataset) -> void { //
  size_t data_size = dataset.size();
  writer.write(data_size);
  for (size_t idx = 0; idx < data_size; ++idx) {
    writer.write(dataset[idx]);
  }
}

template<class T,                                                          //
         size_t N,                                                         //
         bool is_enable_overflow>                                          //
GNET_INLINE auto serializer_write(serializer& writer,                      //
                                  gnet::fixed_vector<T,                    //
                                                     N,                    //
                                                     is_enable_overflow    //
                                                     >& dataset) -> void { //
  size_t data_size = dataset.size();
  writer.write(data_size);
  for (size_t idx = 0; idx < data_size; ++idx) {
    writer.write(dataset[idx]);
  }
}

} // namespace gnet
