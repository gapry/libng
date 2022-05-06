#pragma once

#include <libcxx/util.hpp>
#include <libcxx/UtfUtil.hpp>

#include <platform/os.hpp>
#include <platform/graphics.hpp>

#include <renderer/backend/dx11/TypeDX11.hpp>
#include <renderer/type/RenderDataType.hpp>
#include <renderer/type/RenderPrimitiveType.hpp>
#include <renderer/vertex/VertexSemanticType.hpp>

namespace libng {

struct DX11Util {
  DX11Util() = delete;

  static void throwIfError(HRESULT hr);

  static bool assertIfError(HRESULT hr);

  static void reportError(HRESULT hr);

  static UINT castUINT(size_t v);

  static D3D11_PRIMITIVE_TOPOLOGY getDxPrimitiveTopology(RenderPrimitiveType t);

  static DXGI_FORMAT getDxFormat(RenderDataType v);

  static const char* getDxSemanticName(VertexSemanticType t);

  static String getStrFromHRESULT(HRESULT hr);

private:
  static bool _checkError(HRESULT hr);
};

// clang-format off

LIBNG_INLINE
D3D11_PRIMITIVE_TOPOLOGY DX11Util::getDxPrimitiveTopology(RenderPrimitiveType t) {
  using SRC = RenderPrimitiveType;
  switch (t) {
    case SRC::Points:     return D3D_PRIMITIVE_TOPOLOGY_POINTLIST;
    case SRC::Lines:      return D3D_PRIMITIVE_TOPOLOGY_LINELIST;
    case SRC::Triangles:  return D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
    default: throw LIBNG_ERROR("unknown RenderPrimitiveType");
  }
}

LIBNG_INLINE
const char* DX11Util::getDxSemanticName(VertexSemanticType t) {
  using SRC = VertexSemanticType;
  switch (t) {
    case SRC::Pos:      return "POSITION";
    case SRC::Color:    return "COLOR";
    case SRC::TexCoord: return "TEXCOORD";
    case SRC::Normal:   return "NORMAL";
    case SRC::Tangent:  return "TANGENT";
    case SRC::Binormal: return "BINORMAL";
    default: throw LIBNG_ERROR("unknown VertexLayout_SemanticType");
  }
}

LIBNG_INLINE
DXGI_FORMAT DX11Util::getDxFormat(RenderDataType v) {
  using SRC = RenderDataType;
  switch (v) {
    case SRC::Int8:       return DXGI_FORMAT_R8_SINT; break;
    case SRC::Int8x2:     return DXGI_FORMAT_R8G8_SINT; break;
//  case SRC::Int8x3:     return DXGI_FORMAT_R8G8B8_SINT; break;      //does not support in DX11
    case SRC::Int8x4:     return DXGI_FORMAT_R8G8B8A8_SINT; break;

    case SRC::UInt8:      return DXGI_FORMAT_R8_UINT; break;
    case SRC::UInt8x2:    return DXGI_FORMAT_R8G8_UINT; break;
//  case SRC::UInt8x3:    return DXGI_FORMAT_R8G8B8_UINT; break;      //does not support in DX11
    case SRC::UInt8x4:    return DXGI_FORMAT_R8G8B8A8_UINT; break;

    case SRC::SNorm8:     return DXGI_FORMAT_R8_SNORM; break;
    case SRC::SNorm8x2:   return DXGI_FORMAT_R8G8_SNORM; break;
//  case SRC::SNorm8x3:   return DXGI_FORMAT_R8G8B8_SNORM; break;     //does not support in DX11
    case SRC::SNorm8x4:   return DXGI_FORMAT_R8G8B8A8_SNORM; break;

    case SRC::UNorm8:     return DXGI_FORMAT_R8_UNORM; break;
    case SRC::UNorm8x2:   return DXGI_FORMAT_R8G8_UNORM; break;
//  case SRC::UNorm8x3:   return DXGI_FORMAT_R8G8B8_UNORM; break;     //does not support in DX11
    case SRC::UNorm8x4:   return DXGI_FORMAT_R8G8B8A8_UNORM; break;

    case SRC::Int16:      return DXGI_FORMAT_R16_SINT; break;
    case SRC::Int16x2:    return DXGI_FORMAT_R16G16_SINT; break;
//  case SRC::Int16x3:    return DXGI_FORMAT_R16G16B16_SINT; break;   //does not support in DX11
    case SRC::Int16x4:    return DXGI_FORMAT_R16G16B16A16_SINT; break;

    case SRC::UInt16:     return DXGI_FORMAT_R16_UINT; break;
    case SRC::UInt16x2:   return DXGI_FORMAT_R16G16_UINT; break;
//  case SRC::UInt16x3:   return DXGI_FORMAT_R16G16B16_UINT; break;   //does not support in DX11
    case SRC::UInt16x4:   return DXGI_FORMAT_R16G16B16A16_UINT; break;

    case SRC::SNorm16:    return DXGI_FORMAT_R16_SNORM; break;
    case SRC::SNorm16x2:  return DXGI_FORMAT_R16G16_SNORM; break;
//  case SRC::SNorm16x3:  return DXGI_FORMAT_R16G16B16_SNORM; break;  //does not support in DX11
    case SRC::SNorm16x4:  return DXGI_FORMAT_R16G16B16A16_SNORM; break;

    case SRC::UNorm16:    return DXGI_FORMAT_R16_UNORM; break;
    case SRC::UNorm16x2:  return DXGI_FORMAT_R16G16_UNORM; break;
//  case SRC::UNorm16x3:  return DXGI_FORMAT_R16G16B16_UNORM; break;  //does not support in DX11
    case SRC::UNorm16x4:  return DXGI_FORMAT_R16G16B16A16_UNORM; break;

    case SRC::Int32:      return DXGI_FORMAT_R32_SINT; break;
    case SRC::Int32x2:    return DXGI_FORMAT_R32G32_SINT; break;
//  case SRC::Int32x3:    return DXGI_FORMAT_R32G32B32_SINT; break;   //does not support in DX11
    case SRC::Int32x4:    return DXGI_FORMAT_R32G32B32A32_SINT; break;

    case SRC::UInt32:     return DXGI_FORMAT_R32_UINT; break;
    case SRC::UInt32x2:   return DXGI_FORMAT_R32G32_UINT; break;
//  case SRC::UInt32x3:   return DXGI_FORMAT_R32G32B32_UINT; break;   //does not support in DX11
    case SRC::UInt32x4:   return DXGI_FORMAT_R32G32B32A32_UINT; break;

//  case SRC::SNorm32:    return DXGI_FORMAT_R32_SNORM; break;
//  case SRC::SNorm32x2:  return DXGI_FORMAT_R32G32_SNORM; break;
//  case SRC::SNorm32x3:  return DXGI_FORMAT_R32G32B32_SNORM; break;  //does not support in DX11
//  case SRC::SNorm32x4:  return DXGI_FORMAT_R32G32B32A32_SNORM; break;

//  case SRC::UNorm32:    return DXGI_FORMAT_R32_UNORM; break;
//  case SRC::UNorm32x2:  return DXGI_FORMAT_R32G32_UNORM; break;
//  case SRC::UNorm32x3:  return DXGI_FORMAT_R32G32B32_UNORM; break; //does not support in DX11
//  case SRC::UNorm32x4:  return DXGI_FORMAT_R32G32B32A32_UNORM; break;

    case SRC::Float16:    return DXGI_FORMAT_R16_FLOAT; break;
    case SRC::Float16x2:  return DXGI_FORMAT_R16G16_FLOAT; break;
//  case SRC::Float16x3:  return DXGI_FORMAT_R16G16B16_FLOAT; break; //does not support in DX11
    case SRC::Float16x4:  return DXGI_FORMAT_R16G16B16A16_FLOAT; break;

    case SRC::Float32:    return DXGI_FORMAT_R32_FLOAT; break;
    case SRC::Float32x2:  return DXGI_FORMAT_R32G32_FLOAT; break;
    case SRC::Float32x3:  return DXGI_FORMAT_R32G32B32_FLOAT; break;
    case SRC::Float32x4:  return DXGI_FORMAT_R32G32B32A32_FLOAT; break;
    
    default: throw LIBNG_ERROR("unsupported RenderDataType");
  }
}

LIBNG_INLINE
String DX11Util::getStrFromHRESULT(HRESULT hr) {
  const int bufSize = 4096;
  wchar_t buf[bufSize + 1];

  DWORD langId = 0; // MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT)
  FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM, nullptr, hr, langId, buf, bufSize, nullptr);
  buf[bufSize] = 0; // ensure terminate with 0

  auto str = UtfUtil::toString(buf);
  return str;
}

} // namespace libng