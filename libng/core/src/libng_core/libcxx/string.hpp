#pragma once

#include <fmt/format.h>

#include <libng_core/libcxx/string_view.hpp>
#include <libng_core/types/function.hpp>
#include <libng_core/types/utility.hpp>
#include <third_party/eastl/eastl.hpp>

#define LIBNG_LIBCXX_FORMATTER(T)                                      \
  } /* namespace libng::libcxx */                                      \
  template<>                                                           \
  struct fmt::formatter<libng::libcxx::T> {                            \
    auto parse(fmt::format_parse_context& ctx) {                       \
      return ctx.begin();                                              \
    }                                                                  \
    auto format(const libng::libcxx::T& v, fmt::format_context& ctx) { \
      v.on_fmt(ctx);                                                   \
      return ctx.out();                                                \
    }                                                                  \
  };                                                                   \
  namespace libng::libcxx {                                            \
  // ----------

namespace libng::libcxx {

class string {
public:
  class proxy {
  public:
    proxy(string& str, int idx);

    proxy& operator=(const proxy& rhs);

    proxy& operator=(char chr);

    void copy_on_write();

    char* operator&();

    operator char() const;

  private:
    string& _string;
    int _idx;
  };

  struct info {
    int ref_cnt;
    bool is_shared;
    char* data;

    info(const char* str);

    ~info();
  };

  string();

  string(const char* str);

  string(const string& rhs);

  ~string();

  string& operator=(const string& rhs);

  char* c_str() const;

  proxy operator[](int idx);

  const proxy operator[](int idx) const;

  auto on_fmt(fmt::format_context& ctx) const;

  int ref_cnt() const;

private:
  info* _info = nullptr;

  void is_shared(const string& rhs);
};

LIBNG_INLINE string::proxy::proxy(string& string, int idx)
  : _string(string)
  , _idx(idx) {
}

LIBNG_INLINE void string::proxy::copy_on_write() {
  if (_string._info->ref_cnt > 1) {
    --_string._info->ref_cnt;
    _string._info = new info(_string._info->data);
  }
}

LIBNG_INLINE string::proxy& string::proxy::operator=(const string::proxy& rhs) {
  copy_on_write();
  _string._info->data[_idx] = rhs._string._info->data[rhs._idx];
  return *this;
}

LIBNG_INLINE string::proxy& string::proxy::operator=(char chr) {
  copy_on_write();
  _string._info->data[_idx] = chr;
  return *this;
}

LIBNG_INLINE char* string::proxy::operator&() {
  copy_on_write();
  _string._info->is_shared = false;
  return &(_string._info->data[_idx]);
}

LIBNG_INLINE string::proxy::operator char() const {
  return _string._info->data[_idx];
}

LIBNG_INLINE string::info::info(const char* str)
  : ref_cnt(1)
  , is_shared(true) {
  const int data_size = strlen(str) + 1;
  data                = new char[data_size];
  strcpy_s(data, data_size, str);
}

LIBNG_INLINE string::info::~info() {
  delete[] data;
}

LIBNG_INLINE string::string() {
  string(nullptr); // Issue
}

LIBNG_INLINE string::string(const char* str)
  : _info(new info(str)) {
}

LIBNG_INLINE string::string(const string& rhs) {
  is_shared(rhs);
}

LIBNG_INLINE string& string::operator=(const string& rhs) {
  if (_info == rhs._info) {
    return *this;
  }

  if (--_info->ref_cnt == 0) {
    delete _info;
  }

  is_shared(rhs);
  return *this;
}

LIBNG_INLINE string::~string() {
  if (--_info->ref_cnt == 0) {
    delete _info;
  }
}

LIBNG_INLINE void string::is_shared(const string& rhs) {
  if (rhs._info->is_shared) {
    _info = rhs._info;
    ++_info->ref_cnt;
  } else {
    _info = new info(rhs._info->data);
  }
}

LIBNG_INLINE string::proxy string::operator[](int idx) {
  return string::proxy(*this, idx);
}

LIBNG_INLINE const string::proxy string::operator[](int idx) const {
  return string::proxy(const_cast<string&>(*this), idx);
}

LIBNG_INLINE auto string::on_fmt(fmt::format_context& ctx) const {
  return fmt::format_to(ctx.out(), "{}", _info->data);
}

LIBNG_INLINE char* string::c_str() const {
  return _info->data;
}

LIBNG_INLINE int string::ref_cnt() const {
  return _info->ref_cnt;
}

LIBNG_LIBCXX_FORMATTER(string);

} // namespace libng::libcxx

namespace libng {

template<class T, size_t N, bool bEnableOverflow = true>
struct StringT_Base {
  using type = typename eastl::fixed_string<T, N, bEnableOverflow>;
};

template<class T>
struct StringT_Base<T, 0, true> {
  using type = typename eastl::basic_string<T>;
};

template<class T, size_t N, bool bEnableOverflow = true>
class StringT : public StringT_Base<T, N, bEnableOverflow>::type {
  using Base = typename StringT_Base<T, N, bEnableOverflow>::type;

public:
  StringT() = default;

  StringT(const T* begin, const T* end)
    : Base(begin, end) {
  }

  StringT(StrViewT<T> view)
    : Base(view.data(), view.size()) {
  }

  StringT(StringT&& str)
    : Base(std::move(str)) {
  }

  template<class R>
  void operator=(R&& r) {
    Base::operator=(LIBNG_FORWARD(r));
  }

  void operator+=(StrViewT<T> v) {
    Base::append(v.begin(), v.end());
  }

  template<class R>
  void operator+=(const R& r) {
    Base::operator+=(r);
  }

  StrViewT<T> view() const {
    return StrViewT<T>(data(), size());
  }
};

template<size_t N, bool bEnableOverflow = true>
using StringA_ = StringT<char, N, bEnableOverflow>;

template<size_t N, bool bEnableOverflow = true>
using StringW_ = StringT<wchar_t, N, bEnableOverflow>;

using TempStringA = StringA_<220>;
using TempStringW = StringW_<220>;

using StringA = StringA_<0>;
using StringW = StringW_<0>;

using String = StringA;

template<size_t N>
using String_ = StringA_<N>;

using TempString = TempStringA;

} // namespace libng