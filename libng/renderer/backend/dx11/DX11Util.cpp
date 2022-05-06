#include <platform/graphics.hpp>
#include <types/function.hpp>
#include <exception/error.hpp>
#include <log/log.hpp>

#include <renderer/vertex/VertexSemanticType.hpp>
#include <renderer/type/RenderDataType.hpp>
#include <renderer/backend/dx11/DX11Util.hpp>

namespace libng {

void DX11Util::throwIfError(HRESULT hr) {
  if (!_checkError(hr)) {
    reportError(hr);
    throw LIBNG_ERROR("HRESULT = {}", hr);
  }
}

bool DX11Util::assertIfError(HRESULT hr) {
  if (!_checkError(hr)) {
    reportError(hr);
    LIBNG_ASSERT(false);
    return false;
  }
  return true;
}

bool DX11Util::_checkError(HRESULT hr) {
  return SUCCEEDED(hr);
}

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

UINT DX11Util::castUINT(size_t v) {
  LIBNG_ASSERT(v < UINT_MAX);
  return static_cast<UINT>(v);
}

// clang-format off

LIBNG_INLINE
D3D11_PRIMITIVE_TOPOLOGY DX11Util::getDxPrimitiveTopology(RenderPrimitiveType t) {
	using SRC = RenderPrimitiveType;
	switch (t) {
		case SRC::Points:		  return D3D_PRIMITIVE_TOPOLOGY_POINTLIST;
		case SRC::Lines:		  return D3D_PRIMITIVE_TOPOLOGY_LINELIST;
		case SRC::Triangles:	return D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
		default: throw LIBNG_ERROR("unknown RenderPrimitiveType");
	}
}

LIBNG_INLINE
const char* DX11Util::getDxSemanticName(VertexSemanticType t) {
	using SRC = VertexSemanticType;
	switch (t) {
		case SRC::Pos:			return "POSITION";
		case SRC::Color:		return "COLOR";
		case SRC::TexCoord:	return "TEXCOORD";
		case SRC::Normal:		return "NORMAL";
		case SRC::Tangent:	return "TANGENT";
		case SRC::Binormal:	return "BINORMAL";
		default: throw LIBNG_ERROR("unknown VertexLayout_SemanticType");
	}
}

LIBNG_INLINE
DXGI_FORMAT DX11Util::getDxFormat(RenderDataType v) {
	using SRC = RenderDataType;
	switch (v) {
		case SRC::Int8:			  return DXGI_FORMAT_R8_SINT; break;
		case SRC::Int8x2:		  return DXGI_FORMAT_R8G8_SINT; break;
//	case SRC::Int8x3:		  return DXGI_FORMAT_R8G8B8_SINT; break;      //does not support in DX11
		case SRC::Int8x4:		  return DXGI_FORMAT_R8G8B8A8_SINT; break;

		case SRC::UInt8:		  return DXGI_FORMAT_R8_UINT; break;
		case SRC::UInt8x2:	  return DXGI_FORMAT_R8G8_UINT; break;
//	case SRC::UInt8x3:	  return DXGI_FORMAT_R8G8B8_UINT; break;      //does not support in DX11
		case SRC::UInt8x4:	  return DXGI_FORMAT_R8G8B8A8_UINT; break;

		case SRC::SNorm8:		  return DXGI_FORMAT_R8_SNORM; break;
		case SRC::SNorm8x2:	  return DXGI_FORMAT_R8G8_SNORM; break;
//	case SRC::SNorm8x3:	  return DXGI_FORMAT_R8G8B8_SNORM; break;     //does not support in DX11
		case SRC::SNorm8x4:	  return DXGI_FORMAT_R8G8B8A8_SNORM; break;

		case SRC::UNorm8:		  return DXGI_FORMAT_R8_UNORM; break;
		case SRC::UNorm8x2:	  return DXGI_FORMAT_R8G8_UNORM; break;
//	case SRC::UNorm8x3:	  return DXGI_FORMAT_R8G8B8_UNORM; break;     //does not support in DX11
		case SRC::UNorm8x4:	  return DXGI_FORMAT_R8G8B8A8_UNORM; break;

		case SRC::Int16:		  return DXGI_FORMAT_R16_SINT; break;
		case SRC::Int16x2:	  return DXGI_FORMAT_R16G16_SINT; break;
//	case SRC::Int16x3:	  return DXGI_FORMAT_R16G16B16_SINT; break;   //does not support in DX11
		case SRC::Int16x4:	  return DXGI_FORMAT_R16G16B16A16_SINT; break;

		case SRC::UInt16:		  return DXGI_FORMAT_R16_UINT; break;
		case SRC::UInt16x2:	  return DXGI_FORMAT_R16G16_UINT; break;
//	case SRC::UInt16x3:	  return DXGI_FORMAT_R16G16B16_UINT; break;   //does not support in DX11
		case SRC::UInt16x4:	  return DXGI_FORMAT_R16G16B16A16_UINT; break;

		case SRC::SNorm16:		return DXGI_FORMAT_R16_SNORM; break;
		case SRC::SNorm16x2:	return DXGI_FORMAT_R16G16_SNORM; break;
//	case SRC::SNorm16x3:	return DXGI_FORMAT_R16G16B16_SNORM; break;  //does not support in DX11
		case SRC::SNorm16x4:	return DXGI_FORMAT_R16G16B16A16_SNORM; break;

		case SRC::UNorm16:		return DXGI_FORMAT_R16_UNORM; break;
		case SRC::UNorm16x2:	return DXGI_FORMAT_R16G16_UNORM; break;
//	case SRC::UNorm16x3:	return DXGI_FORMAT_R16G16B16_UNORM; break;  //does not support in DX11
		case SRC::UNorm16x4:	return DXGI_FORMAT_R16G16B16A16_UNORM; break;

		case SRC::Int32:		  return DXGI_FORMAT_R32_SINT; break;
		case SRC::Int32x2:		return DXGI_FORMAT_R32G32_SINT; break;
//	case SRC::Int32x3:		return DXGI_FORMAT_R32G32B32_SINT; break;   //does not support in DX11
		case SRC::Int32x4:		return DXGI_FORMAT_R32G32B32A32_SINT; break;

		case SRC::UInt32:		  return DXGI_FORMAT_R32_UINT; break;
		case SRC::UInt32x2:		return DXGI_FORMAT_R32G32_UINT; break;
//	case SRC::UInt32x3:		return DXGI_FORMAT_R32G32B32_UINT; break;   //does not support in DX11
		case SRC::UInt32x4:		return DXGI_FORMAT_R32G32B32A32_UINT; break;

//	case SRC::SNorm32:		return DXGI_FORMAT_R32_SNORM; break;
//	case SRC::SNorm32x2:	return DXGI_FORMAT_R32G32_SNORM; break;
//	case SRC::SNorm32x3:	return DXGI_FORMAT_R32G32B32_SNORM; break;  //does not support in DX11
//	case SRC::SNorm32x4:	return DXGI_FORMAT_R32G32B32A32_SNORM; break;

//	case SRC::UNorm32:		return DXGI_FORMAT_R32_UNORM; break;
//	case SRC::UNorm32x2:	return DXGI_FORMAT_R32G32_UNORM; break;
//	case SRC::UNorm32x3:	return DXGI_FORMAT_R32G32B32_UNORM; break; //does not support in DX11
//	case SRC::UNorm32x4:	return DXGI_FORMAT_R32G32B32A32_UNORM; break;

		case SRC::Float16:		return DXGI_FORMAT_R16_FLOAT; break;
		case SRC::Float16x2:	return DXGI_FORMAT_R16G16_FLOAT; break;
//	case SRC::Float16x3:	return DXGI_FORMAT_R16G16B16_FLOAT; break; //does not support in DX11
		case SRC::Float16x4:	return DXGI_FORMAT_R16G16B16A16_FLOAT; break;

		case SRC::Float32:		return DXGI_FORMAT_R32_FLOAT; break;
		case SRC::Float32x2:	return DXGI_FORMAT_R32G32_FLOAT; break;
		case SRC::Float32x3:	return DXGI_FORMAT_R32G32B32_FLOAT; break;
		case SRC::Float32x4:	return DXGI_FORMAT_R32G32B32A32_FLOAT; break;
    
		default: throw LIBNG_ERROR("unsupported RenderDataType");
	}
}

} // namespace libng