#include <renderer/backend/dx11/UtilDX11.hpp>
#include <platform/graphics.hpp>
#include <exception/error.hpp>

namespace libng {

void UtilDX11::throwIfError(HRESULT hr) {
  if (!_checkError(hr)) {
    reportError(hr);
    throw LIBNG_ERROR("HRESULT = {}", hr);
  }
}

bool UtilDX11::assertIfError(HRESULT hr) {
  if (!_checkError(hr)) {
    reportError(hr);
    LIBNG_ASSERT(false);
    return false;
  }
  return true;
}

bool UtilDX11::_checkError(HRESULT hr) {
  return SUCCEEDED(hr);
}

inline void UtilDX11::reportError(HRESULT hr) {
}

} // namespace libng