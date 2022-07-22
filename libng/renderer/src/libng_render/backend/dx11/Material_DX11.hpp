#pragma once

#include <libng_render/RendererCommon.hpp>

#include <libng_render/material/Material.hpp>
#include <libng_render/material/ShaderPass.hpp>
#include <libng_render/vertex/VertexLayout.hpp>

#include <libng_render/backend/dx11/GPUBuffer_DX11.hpp>
#include <libng_render/backend/dx11/Material_DX11.hpp>
#include <libng_render/backend/dx11/Shader_DX11.hpp>
#include <libng_render/backend/dx11/Util_DX11.hpp>

namespace libng {

class RenderContext;
class RenderContext_DX11;

class Material_DX11 : public Material {
public:
private:
  using Util = Util_DX11;

  Shader_DX11* shader() {
    return static_cast<Shader_DX11*>(_shader.ptr());
  }

  template<class STAGE>
  static void _bindStageHelper(RenderContext_DX11* ctx, STAGE* stage);

  struct VertexStage_DX11 : public VertexStage {
    using Base = VertexStage;

    VertexStage_DX11(MaterialPass* pass, ShaderVertexStage* shaderStage)
      : Base(pass, shaderStage) {
    }

    void bind(RenderContext_DX11* ctx, const VertexLayout* vertexLayout);

    void bindInputLayout(RenderContext_DX11* ctx, const VertexLayout* vertexLayout);

    void _dxSetConstBuffer(DX11_ID3DDeviceContext* dc, UINT bindPoint, DX11_ID3DBuffer* d3dBuf) {
      dc->VSSetConstantBuffers(bindPoint, 1, &d3dBuf);
    }

    void _dxSetShaderResource(DX11_ID3DDeviceContext* dc, UINT bindPoint, DX11_ID3DShaderResourceView* rv) {
      dc->VSSetShaderResources(bindPoint, 1, &rv);
    }

    void _dxSetSampler(DX11_ID3DDeviceContext* dc, UINT bindPoint, DX11_ID3DSamplerState* ss) {
      dc->VSSetSamplers(bindPoint, 1, &ss);
    }

    Span<ConstBuffer> constBuffers() {
      return _constBuffers;
    }

    Span<TexParam> texParams() {
      return _texParams;
    }

    Shader_DX11::VertexStage_DX11* shaderStage() {
      return static_cast<Shader_DX11::VertexStage_DX11*>(_shaderStage);
    }

    VectorMap<const VertexLayout*, ComPtr<DX11_ID3DInputLayout>> _inputLayoutsMap;
  };

  struct PixelStage_DX11 : public PixelStage {
    using Base          = PixelStage;
    using MyShaderStage = Shader_DX11::PixelStage_DX11;

    PixelStage_DX11(MaterialPass* pass, ShaderPixelStage* shaderStage)
      : Base(pass, shaderStage) {
    }

    void bind(RenderContext_DX11* ctx, const VertexLayout* vertexLayout);

    void _dxSetConstBuffer(DX11_ID3DDeviceContext* dc, UINT bindPoint, DX11_ID3DBuffer* d3dBuf) {
      dc->PSSetConstantBuffers(bindPoint, 1, &d3dBuf);
    }

    void _dxSetShaderResource(DX11_ID3DDeviceContext* dc, UINT bindPoint, DX11_ID3DShaderResourceView* rv) {
      dc->PSSetShaderResources(bindPoint, 1, &rv);
    }

    void _dxSetSampler(DX11_ID3DDeviceContext* dc, UINT bindPoint, DX11_ID3DSamplerState* ss) {
      dc->PSSetSamplers(bindPoint, 1, &ss);
    }

    Span<ConstBuffer> constBuffers() {
      return _constBuffers;
    }

    Span<TexParam> texParams() {
      return _texParams;
    }

    Shader_DX11::PixelStage_DX11* shaderStage() {
      return static_cast<Shader_DX11::PixelStage_DX11*>(_shaderStage);
    }
  };

  struct Pass_DX11 : public Pass {
    Pass_DX11(Material* material, ShaderPass* shaderPass);

    virtual void onBind(RenderContext* ctx, const VertexLayout* vertexLayout) override;

    void _bindRenderState(RenderContext_DX11* ctx);

    VertexStage_DX11 _vertexStageDX11;
    PixelStage_DX11 _pixelStageDX11;

    ComPtr<DX11_ID3DRasterizerState> _rasterizerState;
    ComPtr<DX11_ID3DDepthStencilState> _depthStencilState;
    ComPtr<DX11_ID3DBlendState> _blendState;
  };

  virtual UPtr<Pass> onCreatePass(ShaderPass* shaderPass) override {
    return UPtr<Pass>(new Pass_DX11(this, shaderPass));
  }
};

} // namespace libng