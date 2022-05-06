#include <libcxx/StringUtil.hpp>

namespace libng {

void StringUtil::appendBinToHex(String& result, Span<const u8> data) {
  const char* hex  = "0123456789ABCDEF";
  size_t lineCount = (data.size() + 15) / 16;

  for (size_t line = 0; line < lineCount; line++) {
    size_t lineStart = line * 16;
    for (size_t i = 0; i < 16; i++) {
      size_t index = lineStart + i;

      if (index < data.size()) {
        u8 v = data[index];
        result.push_back(hex[v >> 4]);
        result.push_back(hex[v & 0xF]);
      } else {
        result.append("  ");
      }
      result.push_back(' ');
    }

    result.append("    ");

    for (size_t i = 0; i < 16; i++) {
      size_t index = lineStart + i;

      if (index < data.size()) {
        u8 v = data[index];
        if (v < 32) {
          result.push_back(' '); // non-printable character
        } else {
          result.push_back(v);
        }
      } else {
        result.push_back(' ');
      }
      // result.push_back(' ');
    }
    result.push_back('\n');
  }
}

struct StringUtil_ParseHelper {
  template<class T>
  LIBNG_INLINE static bool tryParseInt(StrView view, T& outValue) {
    static_assert(std::is_signed<T>::value, "");
    String_<256> tmp = view;
    i64 v;
    auto ret = ::sscanf(tmp.c_str(), "%lld", &v);
    if (ret != 1)
      return false;
    if (v < std::numeric_limits<T>::min())
      return false;
    if (v > std::numeric_limits<T>::max())
      return false;
    outValue = static_cast<T>(v);
    return true;
  }

  template<class T>
  LIBNG_INLINE static bool tryParseUInt(StrView view, T& outValue) {
    static_assert(std::is_unsigned<T>::value, "");
    String_<256> tmp = view;
    u64 v;
    auto ret = ::sscanf(tmp.c_str(), "%llu", &v);
    if (ret != 1)
      return false;
    if (v < std::numeric_limits<T>::min())
      return false;
    if (v > std::numeric_limits<T>::max())
      return false;
    outValue = static_cast<T>(v);
    return true;
  }

  static bool tryParseFloat(StrView view, f32& outValue) {
    String_<256> tmp = view;
    auto ret         = ::sscanf(tmp.c_str(), "%f", &outValue);
    if (ret != 1)
      return false;
    return true;
  }

  static bool tryParseFloat(StrView view, f64& outValue) {
    String_<256> tmp = view;
    auto ret         = ::sscanf(tmp.c_str(), "%lf", &outValue);
    if (ret != 1)
      return false;
    return true;
  }
};

// clang-format off
bool StringUtil::tryParse(StrView view, i8&  outValue) { return StringUtil_ParseHelper::tryParseInt(view, outValue); }
bool StringUtil::tryParse(StrView view, i16& outValue) { return StringUtil_ParseHelper::tryParseInt(view, outValue); }
bool StringUtil::tryParse(StrView view, i32& outValue) { return StringUtil_ParseHelper::tryParseInt(view, outValue); }
bool StringUtil::tryParse(StrView view, i64& outValue) { return StringUtil_ParseHelper::tryParseInt(view, outValue); }

bool StringUtil::tryParse(StrView view, u8&  outValue) { return StringUtil_ParseHelper::tryParseUInt(view, outValue); }
bool StringUtil::tryParse(StrView view, u16& outValue) { return StringUtil_ParseHelper::tryParseUInt(view, outValue); }
bool StringUtil::tryParse(StrView view, u32& outValue) { return StringUtil_ParseHelper::tryParseUInt(view, outValue); }
bool StringUtil::tryParse(StrView view, u64& outValue) { return StringUtil_ParseHelper::tryParseUInt(view, outValue); }

bool StringUtil::tryParse(StrView view, f32& outValue) { return StringUtil_ParseHelper::tryParseFloat(view, outValue); }
bool StringUtil::tryParse(StrView view, f64& outValue) { return StringUtil_ParseHelper::tryParseFloat(view, outValue); }

}