#pragma once

#include <libng_render/RendererCommon.hpp>
#include <libng_render/backend/dx11/TypeDX11.hpp>
#include <libng_render/material/ShaderStageMask.hpp>
#include <libng_render/type/RenderDataType.hpp>
#include <libng_render/type/RenderPrimitiveType.hpp>
#include <libng_render/vertex/VertexSemanticType.hpp>

// clang-format off

namespace libng {

#if LIBNG_RENDER_DX11

struct DX11Util {
  DX11Util() = delete;

  static void reportError  (HRESULT hr);
  static bool assertIfError(HRESULT hr);
  static void throwIfError (HRESULT hr);

  static UINT castUINT(size_t v);

  static D3D11_PRIMITIVE_TOPOLOGY getDxPrimitiveTopology(RenderPrimitiveType t);
  static DXGI_FORMAT              getDxFormat           (RenderDataType v);
  static DXGI_FORMAT              getDxColorType        (math::ColorType v);

  static const char* getDxSemanticName(VertexSemanticType t);

  static VertexSemanticType parseDxSemanticName(StrView s);

  static const char* getDxStageProfile(ShaderStageMask s);

  static String getStrFromHRESULT(HRESULT hr);

  static ByteSpan toSpan   (ID3DBlob* blob);
  static StrView  toStrView(ID3DBlob* blob);

private:
  static bool _checkError(HRESULT hr);
};

LIBNG_INLINE void DX11Util::reportError(HRESULT hr) {
  if (!SUCCEEDED(hr)) {
    auto str = getStrFromHRESULT(hr);
    LIBNG_LOG("HRESULT(0x{:0X}) {}", static_cast<u32>(hr), str);
  }
#if 0 && _DEBUG
  auto* d = renderer()->d3dDebug();
  if (d) {
    d->ReportLiveDeviceObjects(D3D11_RLDO_DETAIL);
  }
#endif
}

LIBNG_INLINE
bool DX11Util::assertIfError(HRESULT hr) {
  if (!_checkError(hr)) {
    reportError(hr);
    LIBNG_ASSERT(false);
    return false;
  }
  return true;
}

LIBNG_INLINE
void DX11Util::throwIfError(HRESULT hr) {
  if (!_checkError(hr)) {
    reportError(hr);
    throw LIBNG_ERROR("HRESULT = {}", hr);
  }
}

LIBNG_INLINE UINT DX11Util::castUINT(size_t v) {
  LIBNG_ASSERT(v < UINT_MAX);
  return static_cast<UINT>(v);
}

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
DXGI_FORMAT DX11Util::getDxColorType(math::ColorType v) {
  using SRC = math::ColorType;
  switch (v) {
    case SRC::Rb:     return DXGI_FORMAT_R8_UNORM;
    case SRC::Rf:     return DXGI_FORMAT_R32_FLOAT;

    case SRC::RGb:    return DXGI_FORMAT_R8G8_UNORM;
    case SRC::RGf:    return DXGI_FORMAT_R32G32_FLOAT;

    // case SRC::RGBb:  return DXGI_FORMAT_R8G8B8_UNORM;    // DX Not Support
    // case SRC::RGBf:  return DXGI_FORMAT_R32G32B32_FLOAT; // DX Not Support

    case SRC::RGBAb:  return DXGI_FORMAT_R8G8B8A8_UNORM;
    case SRC::RGBAf:  return DXGI_FORMAT_R32G32B32A32_FLOAT;

    case SRC::BC1:    return DXGI_FORMAT_BC1_UNORM;
    case SRC::BC2:    return DXGI_FORMAT_BC2_UNORM;
    case SRC::BC3:    return DXGI_FORMAT_BC3_UNORM;
    case SRC::BC4:    return DXGI_FORMAT_BC4_UNORM;
    case SRC::BC5:    return DXGI_FORMAT_BC5_UNORM;
    case SRC::BC6h:   return DXGI_FORMAT_BC6H_UF16;
    case SRC::BC7:    return DXGI_FORMAT_BC7_UNORM;

    default: throw LIBNG_ERROR("unsupported ColorType");
  }
}

LIBNG_INLINE
const char* DX11Util::getDxStageProfile(ShaderStageMask s) {
  switch (s) {
    case ShaderStageMask::Vertex: return "vs_5_0";
    case ShaderStageMask::Pixel:  return "ps_5_0";
    default: return "";
  }
}

LIBNG_INLINE
String DX11Util::getStrFromHRESULT(HRESULT hr) {
  const int bufSize = 4096;
  wchar_t buf[bufSize + 1];

  DWORD langId = 0;                         // MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT)
  FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM, //
                nullptr,                    //
                hr,                         //
                langId,                     //
                buf,                        //
                bufSize,                    //
                nullptr);                   //
  buf[bufSize] = 0;                         // ensure terminate with 0

  auto str = UtfUtil::toString(buf);
  return str;
}

LIBNG_INLINE ByteSpan DX11Util::toSpan(ID3DBlob* blob) {
  if (!blob) {
    return ByteSpan();
  }
  return ByteSpan(reinterpret_cast<const u8*>(blob->GetBufferPointer()), //
                  static_cast<size_t>(blob->GetBufferSize()));           //
}

LIBNG_INLINE StrView DX11Util::toStrView(ID3DBlob* blob) {
  return StrView_make(toSpan(blob));
}

LIBNG_INLINE
bool DX11Util::_checkError(HRESULT hr) {
  return SUCCEEDED(hr);
}

#endif

} // namespace libng
