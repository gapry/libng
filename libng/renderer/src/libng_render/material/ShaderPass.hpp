#pragma once

#include <libng_render/RendererCommon.hpp>
#include <libng_render/material/ShaderInfo.hpp>
#include <libng_render/material/ShaderPixelStage.hpp>
#include <libng_render/material/ShaderVertexStage.hpp>

namespace libng {

class Shader;

struct ShaderPass : public NonCopyable {
  ShaderPass(Shader* shader, ShaderInfo::Pass& info);
  virtual ~ShaderPass() = default;

  ShaderVertexStage* vertexStage();
  ShaderPixelStage* pixelStage();

  const ShaderInfo::Pass* info() const;

protected:
  Shader* _shader                 = nullptr;
  ShaderInfo::Pass* _info         = nullptr;
  ShaderVertexStage* _vertexStage = nullptr;
  ShaderPixelStage* _pixelStage   = nullptr;
};

} // namespace libng