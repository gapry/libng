#pragma once

#include <libng_render/RendererCommon.hpp>
#include <libng_render/type/RenderPrimitiveType.hpp>

namespace libng {

class EditMesh : public NonCopyable {
public:
  static const u8 kUvCountMax = 4;

  RenderPrimitiveType primitive = RenderPrimitiveType::Triangles;

  Vector<u32> indices;

  Vector<math::Tuple3f> pos;
  Vector<math::Tuple2f> uv[kUvCountMax];
  Vector<math::Color4b> color;

  Vector<math::Tuple3f> normal;
  Vector<math::Tuple3f> tangent;
  Vector<math::Tuple3f> binormal;

  void clear();
};

} // namespace libng
