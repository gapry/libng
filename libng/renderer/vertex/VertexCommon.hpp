#pragma once

#include <math/Tuple/Tuple2.hpp>
#include <math/Tuple/Tuple3.hpp>

#include <renderer/vertex/VertexType.hpp>
#include <renderer/vertex/VertexBase.hpp>
#include <renderer/vertex/VertexTypeUtil.hpp>
#include <renderer/type/RenderDataType.hpp>
#include <renderer/type/RenderDataTypeUtil.hpp>

#include <renderer/vertex/VertexPos.hpp>
#include <renderer/vertex/VertexColor.hpp>
#include <renderer/vertex/VertexUV.hpp>
#include <renderer/vertex/VertexNormal.hpp>
#include <renderer/vertex/VertexTangent.hpp>
#include <renderer/vertex/VertexBinormal.hpp>

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