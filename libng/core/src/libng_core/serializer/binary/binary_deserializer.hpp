#pragma once

#include <libng_core/exception/error.hpp>
#include <libng_core/libcxx/fixed_vector.hpp>
#include <libng_core/libcxx/span.hpp>
#include <libng_core/libcxx/string.hpp>
#include <libng_core/libcxx/vector.hpp>
#include <libng_core/platform/endian.hpp>
#include <libng_core/serializer/binary/binary_serializer.hpp>
#include <libng_core/types/function.hpp>
#include <libng_core/types/noncopyable.hpp>
#include <libng_core/types/number.hpp>

namespace libng {

// clang-format off

class binary_deserializer : public NonCopyable {
public:
  binary_deserializer(ByteSpan data) 
    : _data(data.data())
    , _cur(data.data())
    , _end(data.end())
  {}

  template<class T> LIBNG_INLINE
  binary_deserializer& operator<<(T& value) { io(value); return *this; }

  template<class T> LIBNG_INLINE
  void io(T& value) { binary_serializer_io(*this, value); }

  LIBNG_INLINE void io(i8 & value)  { io_vary(value); }
  LIBNG_INLINE void io(i16& value)  { io_vary(value); }
  LIBNG_INLINE void io(i32& value)  { io_vary(value); }
  LIBNG_INLINE void io(i64& value)  { io_vary(value); }

  LIBNG_INLINE void io(u8 & value)  { io_vary(value); }
  LIBNG_INLINE void io(u16& value)  { io_vary(value); }
  LIBNG_INLINE void io(u32& value)  { io_vary(value); }
  LIBNG_INLINE void io(u64& value)  { io_vary(value); }

  LIBNG_INLINE void io(f32& value)  { io_fixed(value); }
  LIBNG_INLINE void io(f64& value)  { io_fixed(value); }

  LIBNG_INLINE void io(char& value) { io_vary(value); }
  
  // -------------------------------------------------------------

  LIBNG_INLINE void io_fixed(i8 & value) { _io_fixed_le(value); }
  LIBNG_INLINE void io_fixed(i16& value) { _io_fixed_le(value); }
  LIBNG_INLINE void io_fixed(i32& value) { _io_fixed_le(value); }
  LIBNG_INLINE void io_fixed(i64& value) { _io_fixed_le(value); }

  LIBNG_INLINE void io_fixed(u8 & value) { _io_fixed_le(value); }
  LIBNG_INLINE void io_fixed(u16& value) { _io_fixed_le(value); }
  LIBNG_INLINE void io_fixed(u32& value) { _io_fixed_le(value); }
  LIBNG_INLINE void io_fixed(u64& value) { _io_fixed_le(value); }

  LIBNG_INLINE void io_fixed(f32& value) { _io_fixed_le(value); }
  LIBNG_INLINE void io_fixed(f64& value) { _io_fixed_le(value); }
  
  // -------------------------------------------------------------
  
  LIBNG_INLINE void io_fixed_le(i8 & value) { _io_fixed_le(value); }
  LIBNG_INLINE void io_fixed_le(i16& value) { _io_fixed_le(value); }
  LIBNG_INLINE void io_fixed_le(i32& value) { _io_fixed_le(value); }
  LIBNG_INLINE void io_fixed_le(i64& value) { _io_fixed_le(value); }

  LIBNG_INLINE void io_fixed_le(u8 & value) { _io_fixed_le(value); }
  LIBNG_INLINE void io_fixed_le(u16& value) { _io_fixed_le(value); }
  LIBNG_INLINE void io_fixed_le(u32& value) { _io_fixed_le(value); }
  LIBNG_INLINE void io_fixed_le(u64& value) { _io_fixed_le(value); }

  LIBNG_INLINE void io_fixed_le(f32& value) { _io_fixed_le(value); }
  LIBNG_INLINE void io_fixed_le(f64& value) { _io_fixed_le(value); }

  // -------------------------------------------------------------
  
  LIBNG_INLINE void io_fixed_be(i8 & value) { _io_fixed_be(value); }
  LIBNG_INLINE void io_fixed_be(i16& value) { _io_fixed_be(value); }
  LIBNG_INLINE void io_fixed_be(i32& value) { _io_fixed_be(value); }
  LIBNG_INLINE void io_fixed_be(i64& value) { _io_fixed_be(value); }

  LIBNG_INLINE void io_fixed_be(u8 & value) { _io_fixed_be(value); }
  LIBNG_INLINE void io_fixed_be(u16& value) { _io_fixed_be(value); }
  LIBNG_INLINE void io_fixed_be(u32& value) { _io_fixed_be(value); }
  LIBNG_INLINE void io_fixed_be(u64& value) { _io_fixed_be(value); }

  LIBNG_INLINE void io_fixed_be(f32& value) { _io_fixed_be(value); }
  LIBNG_INLINE void io_fixed_be(f64& value) { _io_fixed_be(value); }

  // -------------------------------------------------------------
  
  LIBNG_INLINE void io_vary(i8 & value)  { _io_vary_signed<u8 >(value); }
  LIBNG_INLINE void io_vary(i16& value)  { _io_vary_signed<u16>(value); }
  LIBNG_INLINE void io_vary(i32& value)  { _io_vary_signed<u32>(value); }
  LIBNG_INLINE void io_vary(i64& value)  { _io_vary_signed<u64>(value); }

  LIBNG_INLINE void io_vary(u8 & value)  { _io_vary_unsigned(value); }
  LIBNG_INLINE void io_vary(u16& value)  { _io_vary_unsigned(value); }
  LIBNG_INLINE void io_vary(u32& value)  { _io_vary_unsigned(value); }
  LIBNG_INLINE void io_vary(u64& value)  { _io_vary_unsigned(value); }

  LIBNG_INLINE void io_vary(char& value) { _io_vary_unsigned(reinterpret_cast<u8&>(value)); }

  // -------------------------------------------------------------
  
  void io_raw(u8* data, size_t dataSize) {
    auto* src = advance(dataSize);
    std::copy(src, src+dataSize, data);;
  }

  // -------------------------------------------------------------
  
  LIBNG_INLINE const u8* advance(size_t n);

  LIBNG_INLINE const u8* cur() const { return _cur; }
  LIBNG_INLINE size_t remain() const { return _end - _cur; }

private:
  template<class T>          LIBNG_INLINE void _io_fixed_le(T& value);
  template<class T>          LIBNG_INLINE void _io_fixed_be(T& value);

  template<class T>          LIBNG_INLINE void _io_vary_unsigned(T& value);
  template<class U, class T> LIBNG_INLINE void _io_vary_signed  (T& value);

  const u8* _data = nullptr;
  const u8* _cur  = nullptr;
  const u8* _end  = nullptr;
};

// clang-format on

LIBNG_INLINE const u8* binary_deserializer::advance(size_t n) {
  if (remain() < n) {
    throw LIBNG_ERROR("{}\n", "binary_deserializer out of range");
  }
  const u8* old = _cur;
  _cur += n;
  return old;
}

template<class T>
LIBNG_INLINE void binary_deserializer::_io_fixed_le(T& value) {
  auto* p = advance(sizeof(value));
  value   = little_endian::to_host::get(*reinterpret_cast<const T*>(p));
}

template<class T>
LIBNG_INLINE void binary_deserializer::_io_fixed_be(T& value) {
  auto* p = advance(sizeof(value));
  value   = big_endian::to_host::get(*reinterpret_cast<const T*>(p));
}

template<class T>
LIBNG_INLINE void binary_deserializer::_io_vary_unsigned(T& value) {
  size_t bit = 0;
  value      = 0;
  for (size_t i = 0; i < sizeof(T) + 1; i++) {
    u8 t = *advance(1);
    value |= static_cast<T>(t & 0x7F) << bit;
    if ((t & 0x80) == 0) {
      return;
    }
    bit += 7;
    if (bit > sizeof(T) * 8) {
      throw LIBNG_ERROR("{}\n", "binary_deserializer out of range");
    }
  }
}

// ZigZag encoding - https://developers.google.com/protocol-buffers/docs/encoding
template<class U, class T>
LIBNG_INLINE void binary_deserializer::_io_vary_signed(T& value) {
  static_assert(sizeof(U) == sizeof(T));
  U tmp;
  _io_vary_unsigned(tmp);
  value = static_cast<T>(tmp >> 1) ^ -static_cast<T>(tmp & 1);
}

template<>
LIBNG_INLINE void binary_serializer_io(binary_deserializer& se, String& v) {
  size_t len = 0;
  se.io(len);
  v.resize(len);
  try {
    se.io_raw(reinterpret_cast<u8*>(v.data()), len);
  } catch (...) {
    v.clear();
    throw;
  }
}

template<class T, size_t N, bool bEnableOverflow>
LIBNG_INLINE void binary_serializer_io(binary_deserializer& se, StringT<T, N, bEnableOverflow>& v) {
  size_t len = 0;
  se.io(len);
  v.resize(len);
  try {
    if (sizeof(T) == 1) {
      se.io_raw(reinterpret_cast<u8*>(v.data()), len);
    } else {
      for (size_t i = 0; i < len; i++) {
        se.io(v[i]);
      }
    }
  } catch (...) {
    v.clear();
    throw;
  }
}

template<class T>
LIBNG_INLINE void binary_serializer_io(binary_deserializer& se, Vector<T>& v) {
  size_t len = 0;
  se.io(len);
  v.resize(len);
  try {
    for (size_t i = 0; i < len; i++) {
      se.io(v[i]);
    }
  } catch (...) {
    v.clear();
    throw;
  }
}

template<class T, size_t N, bool bEnableOverflow>
LIBNG_INLINE void binary_serializer_io(binary_deserializer& se, Vector_<T, N, bEnableOverflow>& v) {
  size_t len = 0;
  se.io(len);
  v.resize(len);
  try {
    for (size_t i = 0; i < len; i++) {
      se.io(v[i]);
    }
  } catch (...) {
    v.clear();
    throw;
  }
}

} // namespace libng