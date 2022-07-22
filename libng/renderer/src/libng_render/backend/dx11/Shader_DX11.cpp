#include <libng_render/backend/dx11/Shader_DX11.hpp>

namespace libng {

Shader_DX11::Shader_DX11(StrView filename)
  : Base(filename) {
  LIBNG_LOG("{}\n", __LIBNG_PRETTY_FUNCTION__);
}

Shader_DX11::~Shader_DX11() {
  LIBNG_LOG("{}\n", __LIBNG_PRETTY_FUNCTION__);
}

void Shader_DX11::loadStageFile(StrView passPath,           //
                                ShaderStageMask stageMask,  //
                                Vector<u8>& outBytecode,    //
                                ShaderStageInfo& outInfo) { //
  auto* profile = Util::getDxStageProfile(stageMask);

  auto filename = Fmt("{}/{}.bin", passPath, profile);
  File::readFile(filename, outBytecode);

  filename += ".json";
  JsonUtil::readFile(filename, outInfo);
}

} // namespace libng
