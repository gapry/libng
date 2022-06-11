#pragma once

#include <libng_core/math/Tuple/Tuple2.hpp>
#include <libng_core/math/Tuple/Tuple3.hpp>
#include <libng_render/vertex/VertexType.hpp>
#include <libng_render/vertex/VertexBase.hpp>
#include <libng_render/vertex/VertexTypeUtil.hpp>
#include <libng_render/type/RenderDataType.hpp>
#include <libng_render/type/RenderDataTypeUtil.hpp>
#include <libng_render/vertex/VertexPos.hpp>
#include <libng_render/vertex/VertexColor.hpp>
#include <libng_render/vertex/VertexUV.hpp>
#include <libng_render/vertex/VertexNormal.hpp>
#include <libng_render/vertex/VertexTangent.hpp>
#include <libng_render/vertex/VertexBinormal.hpp>

// clang-format off
namespace libng {

using VertexPos3f		     = VertexPos<Tuple3f>;
using VertexPos3fColor4b = VertexColor<Color4b, 1, VertexPos3f>; // Issue

template<u8 UV_COUNT> using VertexPosUv              = VertexUV<Tuple2f, UV_COUNT, VertexPos3f>;
template<u8 UV_COUNT> using VertexPosColorUv         = VertexUV<Tuple2f, UV_COUNT, VertexPos3fColor4b>;

template<u8 UV_COUNT> using VertexPosNormalUv        = VertexNormal<Tuple3f,   1, VertexPosUv<UV_COUNT>>;
template<u8 UV_COUNT> using VertexPosColorNormalUv   = VertexNormal<Tuple3f,   1, VertexPosColorUv<UV_COUNT>>;

template<u8 UV_COUNT> using VertexPosTangentUv			 = VertexTangent<Tuple3f,  1, VertexPosNormalUv<UV_COUNT>>;
template<u8 UV_COUNT> using VertexPosColorTangentUv	 = VertexTangent<Tuple3f,  1, VertexPosColorNormalUv<UV_COUNT>>;

template<u8 UV_COUNT> using VertexPosBinormalUv      = VertexBinormal<Tuple3f, 1, VertexPosTangentUv<UV_COUNT>>;
template<u8 UV_COUNT> using VertexPosColorBinormalUv = VertexBinormal<Tuple3f, 1, VertexPosColorTangentUv<UV_COUNT>>;

}