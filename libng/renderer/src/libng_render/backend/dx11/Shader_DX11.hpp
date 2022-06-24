#pragma once

#include <libng_core/libcxx/string_view.hpp>
#include <libng_core/log/log.hpp>
#include <libng_core/types/function.hpp>

#include <libng_render/material/Shader.hpp>

namespace libng {

class Shader_DX11 : public Shader {
public:
  Shader_DX11(StrView filename);
};

} // namespace libng