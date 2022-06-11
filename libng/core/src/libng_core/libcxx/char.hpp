#pragma once

namespace libng {

template<size_t N>
struct CharBySize;

template<>
struct CharBySize<1> {
  using Type = char;
};

template<>
struct CharBySize<2> {
  using Type = char16_t;
};

template<>
struct CharBySize<4> {
  using Type = char32_t;
};

struct WCharUtil {
  using Char = typename CharBySize<sizeof(wchar_t)>::Type;

  Char toChar(wchar_t c) {
    return static_cast<Char>(c);
  }

  wchar_t toWChar(Char c) {
    return static_cast<wchar_t>(c);
  }
};

} // namespace libng