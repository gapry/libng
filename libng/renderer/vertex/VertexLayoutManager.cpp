#include <exception/error.hpp>
#include <renderer/vertex/VertexLayoutManager.hpp>

namespace libng {

VertexLayoutManager* VertexLayoutManager::s_current = nullptr;

VertexLayoutManager::VertexLayoutManager() {
  registerLayout<VertexPos3f>();
  registerLayout<VertexPos3fColor4b>();

#define LIBNG_REGISTER_VERTEX_UV(T) \
  registerLayout<T<1>>();           \
  registerLayout<T<2>>();           \
  registerLayout<T<3>>();           \
  registerLayout<T<4>>();           \
  // ----

  LIBNG_REGISTER_VERTEX_UV(VertexPosUv);
  LIBNG_REGISTER_VERTEX_UV(VertexPosColorUv);

  LIBNG_REGISTER_VERTEX_UV(VertexPosNormalUv);
  LIBNG_REGISTER_VERTEX_UV(VertexPosColorNormalUv);

  LIBNG_REGISTER_VERTEX_UV(VertexPosTangentUv);
  LIBNG_REGISTER_VERTEX_UV(VertexPosColorTangentUv);

  LIBNG_REGISTER_VERTEX_UV(VertexPosBinormalUv);
  LIBNG_REGISTER_VERTEX_UV(VertexPosColorBinormalUv);

#undef LIBNG_REGISTER_VERTEX_UV
}

VertexLayoutManager* VertexLayoutManager::current() {
  static VertexLayoutManager s;
  return &s;
}

const VertexLayout* VertexLayoutManager::getLayout(VertexType type) {
  auto it = _table.find(type);
  if (it == _table.end()) {
    return nullptr;
  }
  return &it->second;
}

VertexLayout* VertexLayoutManager::_createLayout(VertexType type) {
  auto* pLayout = getLayout(type);
  if (pLayout) {
    throw LIBNG_ERROR("VertexLayout: duplicated layout");
  }
  return &_table[type];
}

} // namespace libng