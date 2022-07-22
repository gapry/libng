#pragma once

#include <libng_render/RendererCommon.hpp>

#include <libng_render/material/MaterialPass.hpp>
#include <libng_render/material/MaterialPass_PixelStage.hpp>
#include <libng_render/material/MaterialPass_Stage.hpp>
#include <libng_render/material/MaterialPass_VertexStage.hpp>
#include <libng_render/material/Shader.hpp>

namespace libng {

class Material : public RefCountBase {
public:
  virtual ~Material() = default;

  void setShader(Shader* shader);

  // clang-format off
  void setParam(StrView name, Texture2D*           v) { _setTexParam(name, v); }
  void setParam(StrView name, const float&         v) { _setParam   (name, v); }
  void setParam(StrView name, const math::Tuple2f& v) { _setParam   (name, v); }
  void setParam(StrView name, const math::Tuple3f& v) { _setParam   (name, v); }
  void setParam(StrView name, const math::Tuple4f& v) { _setParam   (name, v); }
  void setParam(StrView name, const math::Mat4f&   v) { _setParam   (name, v); }
  // clang-format on

  using Pass        = MaterialPass;
  using Stage       = MaterialPass_Stage;
  using VertexStage = MaterialPass_VertexStage;
  using PixelStage  = MaterialPass_PixelStage;

  Span<UPtr<Pass>> passes() {
    return _passes;
  }

  Pass* getPass(size_t index) {
    if (index >= _passes.size()) {
      LIBNG_ASSERT(false);
      return nullptr;
    }
    return _passes[index].get();
  }

protected:
  template<class V>
  void _setParam(StrView name, const V& v) {
    for (auto& pass : _passes) {
      if (pass) {
        pass->_setParam(name, v);
      }
    }
  }

  template<class V>
  void _setTexParam(StrView name, const V& v) {
    for (auto& pass : _passes) {
      if (pass) {
        pass->_setTexParam(name, v);
      }
    }
  }

  Vector_<UPtr<Pass>, 2> _passes;
  SPtr<Shader> _shader;

  virtual void onSetShader() {
  }

  virtual UPtr<Pass> onCreatePass(ShaderPass* shaderPass) = 0;
};

} // namespace libng