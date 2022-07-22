#include <libng_render/material/MaterialPass_Stage.hpp>

namespace libng {

MaterialPass_Stage::MaterialPass_Stage(MaterialPass* pass, ShaderStage* shaderStage)
  : _pass(pass)
  , _shaderStage(shaderStage) {
  auto* info = shaderStage->info();
  {
    auto cbCount = info->constBuffers.size();
    _constBuffers.resize(cbCount);

    for (size_t i = 0; i < cbCount; i++) {
      auto& cb = _constBuffers[i];
      cb.create(info->constBuffers[i]);
    }
  }
  {
    auto texCount = info->textures.size();
    _texParams.resize(texCount);

    for (size_t i = 0; i < texCount; i++) {
      auto& t = _texParams[i];
      t.create(info->textures[i]);
    }
  }
}

void MaterialPass_Stage::ConstBuffer::create(const Info& info) {
  _info     = &info;
  _gpuDirty = true;

  cpuBuffer.resize(info.dataSize);

  GPUBuffer::CreateDesc desc;
  desc.type       = GPUBufferType::Const;
  desc.bufferSize = info.dataSize;

  gpuBuffer = Renderer::instance()->createGPUBuffer(desc);
}

void MaterialPass_Stage::ConstBuffer::uploadToGPU() {
  if (!_gpuDirty) {
    return;
  }
  _gpuDirty = false;

  if (!gpuBuffer) {
    return;
  }
  gpuBuffer->uploadToGPU(cpuBuffer);
}

void MaterialPass_Stage::ConstBuffer::errorType() {
  throw LIBNG_ERROR("ConstBuffer setParam type mismatch");
}

Texture* MaterialPass_Stage::TexParam::getUpdatedTexture() {
  if (!_tex) {
    auto* renderer = Renderer::instance();
    switch (_info->dataType) {
      case DataType::Texture2D: return renderer->stockTextures.error; break;
      default: throw LIBNG_ERROR("unsupported texture type");
    }
  }
  // TODO: update texture
  return _tex;
}

} // namespace libng