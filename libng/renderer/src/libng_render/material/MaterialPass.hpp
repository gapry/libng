#pragma once

#include <libng_render/RendererCommon.hpp>

#include <libng_render/RenderContext.hpp>
#include <libng_render/material/MaterialPass.hpp>
#include <libng_render/material/MaterialPass_PixelStage.hpp>
#include <libng_render/material/MaterialPass_Stage.hpp>
#include <libng_render/material/MaterialPass_VertexStage.hpp>
#include <libng_render/material/ShaderPass.hpp>
#include <libng_render/vertex/VertexLayout.hpp>

namespace libng {

class MaterialPass : public NonCopyable {
public:
  virtual ~MaterialPass() = default;

  using Pass        = MaterialPass;
  using Stage       = MaterialPass_Stage;
  using VertexStage = MaterialPass_VertexStage;
  using PixelStage  = MaterialPass_PixelStage;

  void bind(RenderContext* ctx, const VertexLayout* vertexLayout) {
    onBind(ctx, vertexLayout);
  }

  const ShaderInfo::Pass* info() {
    return _shaderPass ? _shaderPass->info() : nullptr;
  }

  friend class Material;

protected:
  MaterialPass(Material* material, ShaderPass* shaderPass)
    : _material(material)
    , _shaderPass(shaderPass) {
  }

  Material* _material     = nullptr;
  ShaderPass* _shaderPass = nullptr;

  virtual void onBind(RenderContext* ctx, const VertexLayout* vertexLayout) = 0;

  template<class V>
  void _setParam(StrView name, const V& v) {
    if (_vertexStage) {
      _vertexStage->_setParam(name, v);
    }
    if (_pixelStage) {
      _pixelStage->_setParam(name, v);
    }
  }

  template<class V>
  void _setTexParam(StrView name, const V& v) {
    if (_vertexStage) {
      _vertexStage->_setTexParam(name, v);
    }
    if (_pixelStage) {
      _pixelStage->_setTexParam(name, v);
    }
  }

  VertexStage* _vertexStage = nullptr;
  PixelStage* _pixelStage   = nullptr;
};

} // namespace libng