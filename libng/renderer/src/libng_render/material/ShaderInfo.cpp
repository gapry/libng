#include <libng_render/material/ShaderInfo.hpp>

namespace libng {

void ShaderInfo::clear() {
  props.clear();
  passes.clear();
}

} // namespace libng