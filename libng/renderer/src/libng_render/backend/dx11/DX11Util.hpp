#pragma once

#include <libng_render/RendererCommon.hpp>
#include <libng_render/backend/dx11/TypeDX11.hpp>
#include <libng_render/material/RenderState.hpp>
#include <libng_render/material/ShaderStageMask.hpp>
#include <libng_render/type/RenderDataType.hpp>
#include <libng_render/type/RenderPrimitiveType.hpp>
#include <libng_render/vertex/VertexSemanticType.hpp>

// clang-format off

namespace libng {

#if LIBNG_RENDER_DX11

struct DX11Util {
  DX11Util() = delete;

  static void   reportError      (HRESULT hr);
  static bool   assertIfError    (HRESULT hr);
  static void   throwIfError     (HRESULT hr);
  static String getStrFromHRESULT(HRESULT hr);

  static UINT castUINT(size_t v);

  static D3D11_PRIMITIVE_TOPOLOGY getDxPrimitiveTopology(RenderPrimitiveType type);
  static DXGI_FORMAT              getDxFormat           (RenderDataType      type);
  static DXGI_FORMAT              getDxColorType        (math::ColorType     type);

  static const char*              getDxStageProfile     (ShaderStageMask    mask);
  static const char*              getDxSemanticName     (VertexSemanticType type);
  static VertexSemanticType       parseDxSemanticName   (StrView            name);

  static D3D11_CULL_MODE          getDxCullMode         (RenderState_Cull        state);
  static D3D11_COMPARISON_FUNC    getDxDepthTestOp      (RenderState_DepthTestOp state);
  static D3D11_BLEND_OP           getDxBlendOp          (RenderState_BlendOp     state);
  static D3D11_BLEND              getDxBlendFactor      (RenderState_BlendFactor state);

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

LIBNG_INLINE UINT DX11Util::castUINT(size_t v) {
  LIBNG_ASSERT(v < UINT_MAX);
  return static_cast<UINT>(v);
}

LIBNG_INLINE
D3D11_PRIMITIVE_TOPOLOGY DX11Util::getDxPrimitiveTopology(RenderPrimitiveType type) {
  using PrimitiveType = RenderPrimitiveType;
  switch (type) {
    case PrimitiveType::Points:    return D3D_PRIMITIVE_TOPOLOGY_POINTLIST;
    case PrimitiveType::Lines:     return D3D_PRIMITIVE_TOPOLOGY_LINELIST;
    case PrimitiveType::Triangles: return D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
    default:                       throw  LIBNG_ERROR("{}\n", "Unknown RenderPrimitiveType");
  }
}

LIBNG_INLINE
DXGI_FORMAT DX11Util::getDxFormat(RenderDataType type) {
  using DataType = RenderDataType;
  switch (type) {
    case DataType::Int8:      return DXGI_FORMAT_R8_SINT;       
    case DataType::Int8x2:    return DXGI_FORMAT_R8G8_SINT;     
//  case DataType::Int8x3:    return DXGI_FORMAT_R8G8B8_SINT;       // does not support in DX11
    case DataType::Int8x4:    return DXGI_FORMAT_R8G8B8A8_SINT; 

    case DataType::UInt8:     return DXGI_FORMAT_R8_UINT; 
    case DataType::UInt8x2:   return DXGI_FORMAT_R8G8_UINT; 
//  case DataType::UInt8x3:   return DXGI_FORMAT_R8G8B8_UINT;       // does not support in DX11
    case DataType::UInt8x4:   return DXGI_FORMAT_R8G8B8A8_UINT; 

    case DataType::SNorm8:    return DXGI_FORMAT_R8_SNORM;   
    case DataType::SNorm8x2:  return DXGI_FORMAT_R8G8_SNORM; 
//  case DataType::SNorm8x3:  return DXGI_FORMAT_R8G8B8_SNORM;      // does not support in DX11
    case DataType::SNorm8x4:  return DXGI_FORMAT_R8G8B8A8_SNORM; 

    case DataType::UNorm8:    return DXGI_FORMAT_R8_UNORM; 
    case DataType::UNorm8x2:  return DXGI_FORMAT_R8G8_UNORM;
//  case DataType::UNorm8x3:  return DXGI_FORMAT_R8G8B8_UNORM;      // does not support in DX11
    case DataType::UNorm8x4:  return DXGI_FORMAT_R8G8B8A8_UNORM; 

    case DataType::Int16:     return DXGI_FORMAT_R16_SINT; 
    case DataType::Int16x2:   return DXGI_FORMAT_R16G16_SINT; 
//  case DataType::Int16x3:   return DXGI_FORMAT_R16G16B16_SINT;    // does not support in DX11
    case DataType::Int16x4:   return DXGI_FORMAT_R16G16B16A16_SINT; 

    case DataType::UInt16:    return DXGI_FORMAT_R16_UINT; 
    case DataType::UInt16x2:  return DXGI_FORMAT_R16G16_UINT; 
//  case DataType::UInt16x3:  return DXGI_FORMAT_R16G16B16_UINT;    // does not support in DX11
    case DataType::UInt16x4:  return DXGI_FORMAT_R16G16B16A16_UINT; 

    case DataType::SNorm16:   return DXGI_FORMAT_R16_SNORM; 
    case DataType::SNorm16x2: return DXGI_FORMAT_R16G16_SNORM; 
//  case DataType::SNorm16x3: return DXGI_FORMAT_R16G16B16_SNORM;   // does not support in DX11
    case DataType::SNorm16x4: return DXGI_FORMAT_R16G16B16A16_SNORM; 

    case DataType::UNorm16:   return DXGI_FORMAT_R16_UNORM; 
    case DataType::UNorm16x2: return DXGI_FORMAT_R16G16_UNORM; 
//  case DataType::UNorm16x3: return DXGI_FORMAT_R16G16B16_UNORM;   // does not support in DX11
    case DataType::UNorm16x4: return DXGI_FORMAT_R16G16B16A16_UNORM; 

    case DataType::Int32:     return DXGI_FORMAT_R32_SINT; 
    case DataType::Int32x2:   return DXGI_FORMAT_R32G32_SINT; 
//  case DataType::Int32x3:   return DXGI_FORMAT_R32G32B32_SINT;    // does not support in DX11
    case DataType::Int32x4:   return DXGI_FORMAT_R32G32B32A32_SINT; 

    case DataType::UInt32:    return DXGI_FORMAT_R32_UINT; 
    case DataType::UInt32x2:  return DXGI_FORMAT_R32G32_UINT; 
//  case DataType::UInt32x3:  return DXGI_FORMAT_R32G32B32_UINT;    // does not support in DX11
    case DataType::UInt32x4:  return DXGI_FORMAT_R32G32B32A32_UINT; 

//  case DataType::SNorm32:   return DXGI_FORMAT_R32_SNORM; 
//  case DataType::SNorm32x2: return DXGI_FORMAT_R32G32_SNORM; 
//  case DataType::SNorm32x3: return DXGI_FORMAT_R32G32B32_SNORM;   // does not support in DX11
//  case DataType::SNorm32x4: return DXGI_FORMAT_R32G32B32A32_SNORM; 

//  case DataType::UNorm32:   return DXGI_FORMAT_R32_UNORM; 
//  case DataType::UNorm32x2: return DXGI_FORMAT_R32G32_UNORM; 
//  case DataType::UNorm32x3: return DXGI_FORMAT_R32G32B32_UNORM;   // does not support in DX11
//  case DataType::UNorm32x4: return DXGI_FORMAT_R32G32B32A32_UNORM; 

    case DataType::Float16:   return DXGI_FORMAT_R16_FLOAT; 
    case DataType::Float16x2: return DXGI_FORMAT_R16G16_FLOAT; 
//  case DataType::Float16x3: return DXGI_FORMAT_R16G16B16_FLOAT;   // does not support in DX11
    case DataType::Float16x4: return DXGI_FORMAT_R16G16B16A16_FLOAT; 

    case DataType::Float32:   return DXGI_FORMAT_R32_FLOAT; 
    case DataType::Float32x2: return DXGI_FORMAT_R32G32_FLOAT; 
    case DataType::Float32x3: return DXGI_FORMAT_R32G32B32_FLOAT; 
    case DataType::Float32x4: return DXGI_FORMAT_R32G32B32A32_FLOAT; 
    
    default:                  throw  LIBNG_ERROR("{}\n", "Unsupported RenderDataType");
  }
}

LIBNG_INLINE
DXGI_FORMAT DX11Util::getDxColorType(math::ColorType type) {
  using ColorType = math::ColorType;
  switch (type) {
    case ColorType::Rb:    return DXGI_FORMAT_R8_UNORM;
    case ColorType::Rf:    return DXGI_FORMAT_R32_FLOAT;

    case ColorType::RGb:   return DXGI_FORMAT_R8G8_UNORM;
    case ColorType::RGf:   return DXGI_FORMAT_R32G32_FLOAT;

 // case ColorType::RGBb:  return DXGI_FORMAT_R8G8B8_UNORM;    // DX Not Support
 // case ColorType::RGBf:  return DXGI_FORMAT_R32G32B32_FLOAT; // DX Not Support

    case ColorType::RGBAb: return DXGI_FORMAT_R8G8B8A8_UNORM;
    case ColorType::RGBAf: return DXGI_FORMAT_R32G32B32A32_FLOAT;

    case ColorType::BC1:   return DXGI_FORMAT_BC1_UNORM;
    case ColorType::BC2:   return DXGI_FORMAT_BC2_UNORM;
    case ColorType::BC3:   return DXGI_FORMAT_BC3_UNORM;
    case ColorType::BC4:   return DXGI_FORMAT_BC4_UNORM;
    case ColorType::BC5:   return DXGI_FORMAT_BC5_UNORM;
    case ColorType::BC6h:  return DXGI_FORMAT_BC6H_UF16;
    case ColorType::BC7:   return DXGI_FORMAT_BC7_UNORM;

    default:               throw  LIBNG_ERROR("{}\n", "Unsupported ColorType");
  }
}

LIBNG_INLINE
const char* DX11Util::getDxStageProfile(ShaderStageMask mask) {
  switch (mask) {
    case ShaderStageMask::Vertex: return "vs_5_0";
    case ShaderStageMask::Pixel:  return "ps_5_0";
    default:                      return "";
  }
}

LIBNG_INLINE
D3D11_CULL_MODE DX11Util::getDxCullMode(RenderState_Cull state) {
  using RenderState = RenderState_Cull;
  switch(state) {
    case RenderState::None:  return D3D11_CULL_NONE;
    case RenderState::Back:  return D3D11_CULL_BACK;
    case RenderState::Front: return D3D11_CULL_FRONT;
    default:                 throw  LIBNG_ERROR("{}\n", "Unsupported CullMode");
  }  
}

LIBNG_INLINE
D3D11_COMPARISON_FUNC DX11Util::getDxDepthTestOp(RenderState_DepthTestOp state) {
  using DepthTestOp = RenderState_DepthTestOp;
  switch(state) {
    case DepthTestOp::Always:       return D3D11_COMPARISON_ALWAYS;
    case DepthTestOp::Never:        return D3D11_COMPARISON_NEVER;
    case DepthTestOp::Equal:        return D3D11_COMPARISON_EQUAL;
    case DepthTestOp::NotEqual:     return D3D11_COMPARISON_NOT_EQUAL;
    case DepthTestOp::Less:         return D3D11_COMPARISON_LESS;
    case DepthTestOp::LessEqual:    return D3D11_COMPARISON_LESS_EQUAL;
    case DepthTestOp::Greater:      return D3D11_COMPARISON_GREATER;
    case DepthTestOp::GreaterEqual: return D3D11_COMPARISON_GREATER_EQUAL;
    default:                        throw  LIBNG_ERROR("{}\n", "Unsupported DepthTestOp");
  }
}

LIBNG_INLINE
D3D11_BLEND_OP DX11Util::getDxBlendOp(RenderState_BlendOp state) {
  using BlendOp = RenderState_BlendOp;
  switch(state) {
    case BlendOp::Add:    return D3D11_BLEND_OP_ADD;  
    case BlendOp::Sub:    return D3D11_BLEND_OP_SUBTRACT;
    case BlendOp::RevSub: return D3D11_BLEND_OP_REV_SUBTRACT;
    case BlendOp::Min:    return D3D11_BLEND_OP_MIN;
    case BlendOp::Max:    return D3D11_BLEND_OP_MAX;
    default:              throw  LIBNG_ERROR("{}\n", "Unsupported BlendOp");
  }
}

LIBNG_INLINE
D3D11_BLEND DX11Util::getDxBlendFactor(RenderState_BlendFactor state) {
  using Factor = RenderState_BlendFactor;  
  switch(state) {
    case Factor::Zero:               return D3D11_BLEND_ZERO;
    case Factor::One:                return D3D11_BLEND_ONE;
    case Factor::SrcAlphaSaturate:   return D3D11_BLEND_SRC_ALPHA_SAT;
    case Factor::SrcAlpha:           return D3D11_BLEND_SRC_ALPHA;
    case Factor::DstAlpha:           return D3D11_BLEND_DEST_ALPHA;
    case Factor::SrcColor:           return D3D11_BLEND_SRC_COLOR;
    case Factor::DstColor:           return D3D11_BLEND_DEST_COLOR;
    case Factor::ConstColor:         return D3D11_BLEND_BLEND_FACTOR;
//  case Factor::ConstAlpha:         return;
    case Factor::OneMinusSrcAlpha:   return D3D11_BLEND_INV_SRC_ALPHA;
    case Factor::OneMinusDstAlpha:   return D3D11_BLEND_INV_DEST_ALPHA;
    case Factor::OneMinusSrcColor:   return D3D11_BLEND_INV_SRC_COLOR;
    case Factor::OneMinusDstColor:   return D3D11_BLEND_INV_DEST_COLOR;
    case Factor::OneMinusConstColor: return D3D11_BLEND_INV_BLEND_FACTOR;
//  case Factor::OneMinusConstAlpha: return;
    default:                         throw  LIBNG_ERROR("{}\n", "Unsupported BlendFactor");
  }
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
