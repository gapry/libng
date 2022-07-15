#pragma once

#include <libng_core/math/Color/ColorCompressType.hpp>
#include <libng_core/math/Color/ColorElementType.hpp>
#include <libng_core/math/Color/ColorModel.hpp>
#include <libng_core/math/Color/ColorType.hpp>

namespace libng {

template<ColorType BC, ColorModel MODEL, int BITS, int BLOCK>
struct ColorBC {
  using Element = void;

  static constexpr ColorType kColorType    = BC;
  static constexpr ColorModel kColorModel  = MODEL;
  static constexpr int kAlphaBits          = BITS;
  static constexpr int kBytesPerPixelBlock = BLOCK;
};

// clang-format off
using ColorBC1  = ColorBC<ColorType::BC1,  ColorModel::BlockCompression, 1, 8>;
using ColorBC2  = ColorBC<ColorType::BC2,  ColorModel::BlockCompression, 4, 16>;
using ColorBC3  = ColorBC<ColorType::BC3,  ColorModel::BlockCompression, 8, 16>;
using ColorBC4  = ColorBC<ColorType::BC4,  ColorModel::BlockCompression, 0, 8>;
using ColorBC5  = ColorBC<ColorType::BC5,  ColorModel::BlockCompression, 0, 16>;
using ColorBC6h = ColorBC<ColorType::BC6h, ColorModel::BlockCompression, 0, 16>;
using ColorBC7  = ColorBC<ColorType::BC7,  ColorModel::BlockCompression, 8, 16>;

} // namespace libng