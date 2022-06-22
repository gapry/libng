#pragma once

#include <libng_core/libcxx/span.hpp>
#include <libng_core/libcxx/string.hpp>
#include <libng_core/libcxx/string_view.hpp>
#include <libng_core/types/function.hpp>
#include <libng_core/types/number.hpp>

namespace libng {

struct StringUtil {
  StringUtil() = delete;

  static void binToHex(String& result, Span<u8> data) {
    result.clear();
    appendBinToHex(result, data);
  }

  static void appendBinToHex(String& result, Span<const u8> data);

  static bool hasChar(StrView view, char ch) {
    return StrView::npos != view.find(ch);
  }

  static std::pair<StrView, StrView> splitByChar(StrView view, StrView seperators);
  static std::pair<StrView, StrView> splitByChar(StrView view, char seperator);

  static StrView trimChar(StrView view, StrView seperators);

  static bool tryParse(StrView view, i8& outValue);
  static bool tryParse(StrView view, i16& outValue);
  static bool tryParse(StrView view, i32& outValue);
  static bool tryParse(StrView view, i64& outValue);

  static bool tryParse(StrView view, u8& outValue);
  static bool tryParse(StrView view, u16& outValue);
  static bool tryParse(StrView view, u32& outValue);
  static bool tryParse(StrView view, u64& outValue);

  static bool tryParse(StrView view, f32& outValue);
  static bool tryParse(StrView view, f64& outValue);
};

LIBNG_INLINE
std::pair<StrView, StrView> StringUtil::splitByChar(StrView view, StrView seperators) {
  auto* s = view.begin();
  auto* e = view.end();
  for (auto* p = s; p < e; p++) {
    if (hasChar(seperators, *p)) {
      auto r0 = StrView(s, p - s);
      auto r1 = StrView(p + 1, e - p - 1);
      return {r0, r1};
    }
  }
  return {view, StrView()};
}

LIBNG_INLINE
std::pair<libng::StrView, libng::StrView> StringUtil::splitByChar(StrView view, char seperator) {
  return splitByChar(view, StrView(&seperator, 1));
}

LIBNG_INLINE
StrView StringUtil::trimChar(StrView view, StrView charList) {
  auto* p = view.begin();
  auto* e = view.end();
  for (; p < e; p++) {
    if (!hasChar(charList, *p))
      break;
  }
  return StrView(p, e - p);
}

} // namespace libng
