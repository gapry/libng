#pragma once

#include <renderer/backend/dx11/TypeDX11.hpp>

namespace libng {

struct UtilDX11 {
  UtilDX11() = delete;

  static void throwIfError(HRESULT hr);

  static bool assertIfError(HRESULT hr);

  static void reportError(HRESULT hr);

private:
  static bool _checkError(HRESULT hr);
};

} // namespace libng