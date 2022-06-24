#include <libng_render/backend/dx11/DX11Util.hpp>

namespace libng {

VertexSemanticType DX11Util::parseDxSemanticName(StrView s) {
  VertexSemanticType v;

  if (s == "SV_POSITION") {
    return VertexSemanticType::POSITION;
  }

  if (!enumTryParse(v, s)) {
    throw LIBNG_ERROR("unknown VertexLayout_SemanticType {}", s);
  }
  return v;
}

const char* DX11Util::getDxSemanticName(VertexSemanticType v) {
  const char* s = enumStr(v);
  if (!s) {
    throw LIBNG_ERROR("unknown VertexLayout_SemanticType {}", v);
  }
  return s;
}

} // namespace libng