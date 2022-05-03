#pragma once

#include <renderer/RenderContext.hpp>

namespace libng {

class RenderContextDX11 : public RenderContext {
  using Base = RenderContext;

public:
  RenderContextDX11(CreateDesc& desc);
};

} // namespace libng