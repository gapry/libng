#pragma once

#include <compiler/shader/ShaderCodeGen.hpp>

namespace libng {

class CompilerOpenGL : public ShaderCodeGen {
public:
  CompilerOpenGL(CreateDesc& desc);
};

} // namespace libng