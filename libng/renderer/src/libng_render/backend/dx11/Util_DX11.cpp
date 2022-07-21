#include <libng_render/backend/dx11/Util_DX11.hpp>

namespace libng {

#if LIBNG_RENDER_DX11

VertexSemanticType Util_DX11::parseDxSemanticName(StrView name) {
  VertexSemanticType type;

  if (name == "SV_POSITION") {
    return VertexSemanticType::POSITION;
  }

  if (!enumTryParse(type, name)) {
    throw LIBNG_ERROR("unknown VertexLayout_SemanticType {}", name);
  }
  return type;
}

const char* Util_DX11::getDxSemanticName(VertexSemanticType type) {
  const char* name = enumStr(type);
  if (!name) {
    throw LIBNG_ERROR("unknown VertexLayout_SemanticType {}", type);
  }
  return name;
}

#endif

} // namespace libng