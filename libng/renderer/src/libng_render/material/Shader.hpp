#pragma once

#include <libng_render/RendererCommon.hpp>
#include <libng_render/material/ShaderInfo.hpp>
#include <libng_render/material/ShaderPass.hpp>

namespace libng {

class Shader : public RefCountBase {
public:
  Shader(StrView filename);
  virtual ~Shader();

  const String& filename() const;
  const ShaderInfo* info() const;

  Span<UPtr<ShaderPass>> passes();

protected:
  String _filename;
  ShaderInfo _info;
  Vector_<UPtr<ShaderPass>, 2> _passes;
};

} // namespace libng