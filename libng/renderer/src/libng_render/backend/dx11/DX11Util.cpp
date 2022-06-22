#include <libng_core/exception/error.hpp>
#include <libng_core/log/log.hpp>
#include <libng_core/platform/graphics.hpp>
#include <libng_core/types/function.hpp>
#include <libng_render/backend/dx11/DX11Util.hpp>
#include <libng_render/type/RenderDataType.hpp>
#include <libng_render/vertex/VertexSemanticType.hpp>

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

} // namespace libng