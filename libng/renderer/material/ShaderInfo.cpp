#include <renderer/material/ShaderInfo.hpp>

namespace libng {

void ShaderInfo::clear() {
  props.clear();  
  passes.clear();
}

}