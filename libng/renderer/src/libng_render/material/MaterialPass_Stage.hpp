#pragma once

#include <libng_render/buffer/GPUBuffer.hpp>
#include <libng_render/material/ShaderStageInfo.hpp>

namespace libng {

class Material;
class MaterialPass;

struct MaterialPass_Stage : public NonCopyable {
  using Pass = MaterialPass;

  friend class Pass;

protected:
  struct ConstBuffer {
    Vector<u8> cpuBuffer;
    SPtr<GPUBuffer> gpuBuffer;
  };
};

} // namespace libng