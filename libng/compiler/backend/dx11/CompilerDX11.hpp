#pragma once

#include <platform/os.hpp>
#include <file/MemMapFile.hpp>
#include <compiler/ShaderCodeGen.hpp>

#include <d3dcompiler.h>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")

namespace libng {

class CompilerDX11 : public ShaderCodeGen {
public:
  CompilerDX11(CreateDesc& desc);
};

} // namespace libng