#pragma once

#include <libcxx/util.hpp>
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

} // namespace libng