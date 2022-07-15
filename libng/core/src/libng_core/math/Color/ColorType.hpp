#pragma once

#include <libng_core/math/Color/ColorCompressType.hpp>
#include <libng_core/math/Color/ColorElementType.hpp>
#include <libng_core/math/Color/ColorModel.hpp>
#include <libng_core/types/function.hpp>
#include <libng_core/types/number.hpp>

namespace libng {

enum class ColorType : u16;

constexpr ColorType ColorType_make(ColorModel model, ColorElementType elem) {
  return static_cast<ColorType>((static_cast<u32>(model) << 8) | (static_cast<u32>(elem)));
}

constexpr ColorType ColorType_make(ColorModel model, ColorCompressType compress) {
  return static_cast<ColorType>((static_cast<u32>(model) << 8) | (static_cast<u32>(compress)));
}

#define ColorType_ENUM_LIST(E)                                                     \
  E(None, )                                                                        \
  E(Rb, = ColorType_make(ColorModel::R, ColorElementType::UNorm8))                 \
  E(Rs, = ColorType_make(ColorModel::R, ColorElementType::UNorm16))                \
  E(Rh, = ColorType_make(ColorModel::R, ColorElementType::Float16))                \
  E(Rf, = ColorType_make(ColorModel::R, ColorElementType::Float32))                \
                                                                                   \
  E(Lb, = ColorType_make(ColorModel::L, ColorElementType::UNorm8))                 \
  E(Ls, = ColorType_make(ColorModel::L, ColorElementType::UNorm16))                \
  E(Lh, = ColorType_make(ColorModel::L, ColorElementType::Float16))                \
  E(Lf, = ColorType_make(ColorModel::L, ColorElementType::Float32))                \
                                                                                   \
  E(LAb, = ColorType_make(ColorModel::LA, ColorElementType::UNorm8))               \
  E(LAs, = ColorType_make(ColorModel::LA, ColorElementType::UNorm16))              \
  E(LAh, = ColorType_make(ColorModel::LA, ColorElementType::Float16))              \
  E(LAf, = ColorType_make(ColorModel::LA, ColorElementType::Float32))              \
                                                                                   \
  E(RGb, = ColorType_make(ColorModel::RG, ColorElementType::UNorm8))               \
  E(RGs, = ColorType_make(ColorModel::RG, ColorElementType::UNorm16))              \
  E(RGh, = ColorType_make(ColorModel::RG, ColorElementType::Float16))              \
  E(RGf, = ColorType_make(ColorModel::RG, ColorElementType::Float32))              \
                                                                                   \
  E(RGBb, = ColorType_make(ColorModel::RGB, ColorElementType::UNorm8))             \
  E(RGBs, = ColorType_make(ColorModel::RGB, ColorElementType::UNorm16))            \
  E(RGBh, = ColorType_make(ColorModel::RGB, ColorElementType::Float16))            \
  E(RGBf, = ColorType_make(ColorModel::RGB, ColorElementType::Float32))            \
                                                                                   \
  E(RGBAb, = ColorType_make(ColorModel::RGBA, ColorElementType::UNorm8))           \
  E(RGBAs, = ColorType_make(ColorModel::RGBA, ColorElementType::UNorm16))          \
  E(RGBAh, = ColorType_make(ColorModel::RGBA, ColorElementType::Float16))          \
  E(RGBAf, = ColorType_make(ColorModel::RGBA, ColorElementType::Float32))          \
                                                                                   \
  E(BC1, = ColorType_make(ColorModel::BlockCompression, ColorCompressType::BC1))   \
  E(BC2, = ColorType_make(ColorModel::BlockCompression, ColorCompressType::BC2))   \
  E(BC3, = ColorType_make(ColorModel::BlockCompression, ColorCompressType::BC3))   \
  E(BC4, = ColorType_make(ColorModel::BlockCompression, ColorCompressType::BC4))   \
  E(BC5, = ColorType_make(ColorModel::BlockCompression, ColorCompressType::BC5))   \
  E(BC6h, = ColorType_make(ColorModel::BlockCompression, ColorCompressType::BC6h)) \
  E(BC7, = ColorType_make(ColorModel::BlockCompression, ColorCompressType::BC7))   \
//----
LIBNG_ENUM_CLASS(ColorType, u16)

} // namespace libng

// Workaround
namespace libng::math {

using ColorType = libng::ColorType;

}