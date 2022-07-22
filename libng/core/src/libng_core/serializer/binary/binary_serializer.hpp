#pragma once

#include <libng_core/libcxx/fixed_vector.hpp>
#include <libng_core/libcxx/string.hpp>
#include <libng_core/libcxx/vector.hpp>
#include <libng_core/platform/endian.hpp>
#include <libng_core/types/function.hpp>
#include <libng_core/types/noncopyable.hpp>
#include <libng_core/types/number.hpp>

namespace libng {

template<class SE, class T>
LIBNG_INLINE void binary_serializer_io(SE& se, T& value) {
  value.io(se);
}

// clang-format off
class binary_serializer : public NonCopyable {
public:
  binary_serializer(Vector<u8>& buf) : _buff(&buf) {}
  
  template<class T> 
  LIBNG_INLINE binary_serializer& operator<<(T& value) { io(value); return *this; }

  template<class T> 
  LIBNG_INLINE void io(T& value) { binary_serializer_io(*this, value); }

  LIBNG_INLINE void io(i8 & value)  { io_vary(value);  }
  LIBNG_INLINE void io(i16& value)  { io_vary(value);  }
  LIBNG_INLINE void io(i32& value)  { io_vary(value);  }
  LIBNG_INLINE void io(i64& value)  { io_vary(value);  }

  LIBNG_INLINE void io(u8 & value)  { io_vary(value);  }
  LIBNG_INLINE void io(u16& value)  { io_vary(value);  }
  LIBNG_INLINE void io(u32& value)  { io_vary(value);  }
  LIBNG_INLINE void io(u64& value)  { io_vary(value);  }

  LIBNG_INLINE void io(f32& value)  { io_fixed(value); }
  LIBNG_INLINE void io(f64& value)  { io_fixed(value); }

  LIBNG_INLINE void io(char& value) { io_vary(value);  }

  LIBNG_INLINE void io_fixed(i8 & value)  { _io_fixed(value); }
  LIBNG_INLINE void io_fixed(i16& value)  { _io_fixed(value); }
  LIBNG_INLINE void io_fixed(i32& value)  { _io_fixed(value); }
  LIBNG_INLINE void io_fixed(i64& value)  { _io_fixed(value); }

  LIBNG_INLINE void io_fixed(u8 & value)  { _io_fixed(value); }
  LIBNG_INLINE void io_fixed(u16& value)  { _io_fixed(value); }
  LIBNG_INLINE void io_fixed(u32& value)  { _io_fixed(value); }
  LIBNG_INLINE void io_fixed(u64& value)  { _io_fixed(value); }

  LIBNG_INLINE void io_fixed(f32& value)  { _io_fixed(value); }
  LIBNG_INLINE void io_fixed(f64& value)  { _io_fixed(value); }

  LIBNG_INLINE void io_vary(i8 & value)  { _io_vary_signed<u8 >(value); }
  LIBNG_INLINE void io_vary(i16& value)  { _io_vary_signed<u16>(value); }
  LIBNG_INLINE void io_vary(i32& value)  { _io_vary_signed<u32>(value); }
  LIBNG_INLINE void io_vary(i64& value)  { _io_vary_signed<u64>(value); }

  LIBNG_INLINE void io_vary(u8 & value)  { _io_vary_unsigned(value); }
  LIBNG_INLINE void io_vary(u16& value)  { _io_vary_unsigned(value); }
  LIBNG_INLINE void io_vary(u32& value)  { _io_vary_unsigned(value); }
  LIBNG_INLINE void io_vary(u64& value)  { _io_vary_unsigned(value); }

  LIBNG_INLINE void io_vary(char& value) { _io_vary_unsigned(reinterpret_cast<u8&>(value)); }

  LIBNG_INLINE u8* advance(size_t n);

  void io_raw(const u8* data, size_t dataSize) {
    _buff->reserve(_buff->size() + dataSize);
    _buff->insert(_buff->end(), data, data + dataSize);
  }

private:
  template<class T>          LIBNG_INLINE void _io_fixed        (T& value);
  template<class T>          LIBNG_INLINE void _io_vary_unsigned(T& value);
  template<class U, class T> LIBNG_INLINE void _io_vary_signed  (T& value);

private:
  Vector<u8>* _buff = nullptr;
};

// clang-format on

LIBNG_INLINE
u8* binary_serializer::advance(size_t n) {
  size_t oldSize = _buff->size();
  _buff->resize(oldSize + n);
  return _buff->data() + oldSize;
}

template<class T>
LIBNG_INLINE void binary_serializer::_io_fixed(T& value) {
  auto* p                  = advance(sizeof(value));
  *reinterpret_cast<T*>(p) = little_endian::from_host::get(value);
}

template<class T>
LIBNG_INLINE void binary_serializer::_io_vary_unsigned(T& value) {
  T tmp = value;
  for (size_t i = 0; i < sizeof(T) + 1; i++) {
    u8 highBit = tmp >= 0x80 ? 0x80 : 0;
    _buff->push_back(static_cast<u8>(tmp) | highBit);
    tmp >>= 7;
    if (tmp == 0) {
      return;
    }
  }
  throw LIBNG_ERROR("{}\n", __LIBNG_PRETTY_FUNCTION__);
}

// ZigZag encoding - https://developers.google.com/protocol-buffers/docs/encoding
template<class U, class T>
LIBNG_INLINE void binary_serializer::_io_vary_signed(T& value) {
  static_assert(sizeof(U) == sizeof(T));
  U tmp = static_cast<U>((value << 1) ^ (value >> (sizeof(T) * 8 - 1)));
  _io_vary_unsigned(tmp);
}

template<>
LIBNG_INLINE void binary_serializer_io(binary_serializer& se, String& v) {
  size_t len = v.size();
  se.io(len);
  se.io_raw(reinterpret_cast<const u8*>(v.data()), len);
}

template<class T, size_t N, bool bEnableOverflow>
LIBNG_INLINE void binary_serializer_io(binary_serializer& se, StringT<T, N, bEnableOverflow>& v) {
  size_t len = v.size();
  se.io(len);
  if (sizeof(T) == 1) {
    se.io_raw(reinterpret_cast<const u8*>(v.data()), len);
  } else {
    for (size_t i = 0; i < len; i++) {
      se.io(v[i]);
    }
  }
}

template<class T>
LIBNG_INLINE void binary_serializer_io(binary_serializer& se, Vector<T>& v) {
  size_t len = v.size();
  se.io(len);
  for (size_t i = 0; i < len; i++) {
    se.io(v[i]);
  }
}

template<class T, size_t N, bool bEnableOverflow>
LIBNG_INLINE void binary_serializer_io(binary_serializer& se, Vector_<T, N, bEnableOverflow>& v) {
  size_t len = v.size();
  se.io(len);
  for (size_t i = 0; i < len; i++) {
    se.io(v[i]);
  }
}

} // namespace libng