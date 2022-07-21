#pragma once

#include <libng_render/RendererCommon.hpp>
#include <libng_render/material/ShaderPropType.hpp>
#include <libng_render/material/ShaderPropTypeUtil.hpp>

namespace libng {

struct ShaderPropValueConstPtr {
  using Type = ShaderPropType;

  Type type        = Type::None;
  const void* data = nullptr;
  size_t dataSize  = 0;

  ShaderPropValueConstPtr() = default;

  template<class V>
  ShaderPropValueConstPtr(const V& val) {
    type     = ShaderPropTypeUtil::get<V>();
    data     = &val;
    dataSize = sizeof(val);
  }

  template<class V>
  const V& asValue() {
    if (type != ShaderPropTypeUtil::get<V>()) {
      throw LIBNG_ERROR("{}\n", "Invalid ShaderPropType");
    }
    return *reinterpret_cast<const V*>(data);
  }
};

} // namespace libng