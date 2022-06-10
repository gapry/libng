#pragma once

#include <compiler/shader/ShaderCodeGen.hpp>

namespace libng {

class CodeGenOpenGL : public ShaderCodeGen {
public:
  CodeGenOpenGL(CreateDesc& desc);
};

} // namespace libng