#pragma once

#include <libng_render/buffer/GPUBuffer.hpp>
#include <libng_render/material/ShaderStage.hpp>
#include <libng_render/material/ShaderStageInfo.hpp>
#include <libng_render/textures/Texture.hpp>
#include <libng_render/textures/Texture2D.hpp>
#include <libng_render/type/RenderDataTypeUtil.hpp>

namespace libng {

class Material;
class MaterialPass;

struct MaterialPass_Stage : public NonCopyable {
  using Pass = MaterialPass;

  virtual ~MaterialPass_Stage() = default;

  MaterialPass_Stage(MaterialPass* pass, ShaderStage* shaderStage);

  const ShaderStageInfo* info() const {
    return _shaderStage->info();
  }

private:
  friend class MaterialPass;

protected:
  struct ConstBuffer {
    using DataType = ShaderStageInfo::DataType;
    using Info     = ShaderStageInfo::ConstBuffer;
    using VarInfo  = ShaderStageInfo::Variable;

    Vector<u8> cpuBuffer;
    SPtr<GPUBuffer> gpuBuffer;

    template<class V>
    void setParam(const Info& cbInfo, StrView name, const V& value) {
      auto* varInfo = cbInfo.findVariable(name);
      if (!varInfo) {
        return;
      }
      _setParam(varInfo, value);
    }

    void create(const Info& info);

    void uploadToGPU();

    const Info* info() const {
      return _info;
    }

  private:
    const Info* _info = nullptr;
    bool _gpuDirty    = false;

    // clang-format off
    void _setParam(const VarInfo* varInfo, const float&         value) { _setParamCheckType(varInfo, value); }
    void _setParam(const VarInfo* varInfo, const math::Tuple2f& value) { _setParamCheckType(varInfo, value); }
    void _setParam(const VarInfo* varInfo, const math::Tuple3f& value) { _setParamCheckType(varInfo, value); }
    void _setParam(const VarInfo* varInfo, const math::Tuple4f& value) { _setParamCheckType(varInfo, value); }
    void _setParam(const VarInfo* varInfo, const math::Mat4f&   value) { _setParamCheckType(varInfo, value); }
    // clang-format on

    template<class V>
    void _setParamCheckType(const VarInfo* varInfo, const V& value) {
      if (varInfo->dataType != RenderDataTypeUtil::get<V>()) {
        errorType();
        return;
      }
      _setValueAs(varInfo, value);
    }

    template<class V>
    void _setValueAs(const VarInfo* varInfo, const V& value) {
      auto end = varInfo->offset + sizeof(value);
      if (end > cpuBuffer.size()) {
        throw LIBNG_ERROR("ConstBuffer setParam out of range");
      }
      auto* dst                  = cpuBuffer.data() + varInfo->offset;
      *reinterpret_cast<V*>(dst) = value;
      _gpuDirty                  = true;
    }

    void errorType();
  };

  template<class V>
  void _setParam(StrView name, const V& v) {
    if (!_shaderStage) {
      return;
    }
    size_t i = 0;
    for (auto& cb : _constBuffers) {
      cb.setParam(info()->constBuffers[i], name, v);
      i++;
    }
  }

  struct TexParam {
    using DataType = ShaderStageInfo::DataType;
    using Info     = ShaderStageInfo::Texture;

    void create(const Info& info) {
      _info = &info;
    }

    Texture* getUpdatedTexture();

    StrView name() const {
      return _info->name;
    }

    int bindPoint() const {
      return _info->bindPoint;
    }

    DataType dataType() const {
      return _info->dataType;
    }

    template<class TEX>
    void setTexParam(TEX* tex) {
      if (_info->dataType != RenderDataTypeUtil::get<TEX>()) {
        _tex.reset(nullptr);
        throw LIBNG_ERROR("invalid texture type");
      }
      _tex = tex;
    }

  protected:
    SPtr<Texture> _tex;
    const Info* _info = nullptr;
  };

  template<class V>
  void _setTexParam(StrView name, V* texture) {
    if (!texture) {
      LIBNG_ASSERT(false);
      return;
    }
    for (auto& p : _texParams) {
      if (0 == p.name().compare(name)) {
        p.setTexParam(texture);
        break;
      }
    }
  }

  Pass* _pass               = nullptr;
  ShaderStage* _shaderStage = nullptr;

  Vector_<ConstBuffer, 4> _constBuffers;
  Vector_<TexParam, 4> _texParams;
};

} // namespace libng