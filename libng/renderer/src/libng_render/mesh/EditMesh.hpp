#pragma once

#include <libng_core/types/noncopyable.hpp>
#include <libng_core/types/number.hpp>
#include <libng_core/libcxx/vector.hpp>
#include <libng_core/math/Color.hpp>
#include <libng_core/math/Tuple/Tuple2.hpp>
#include <libng_core/math/Tuple/Tuple3.hpp>
#include <libng_render/type/RenderPrimitiveType.hpp>

namespace libng {

class EditMesh : public NonCopyable {
public:
  static const u8 kUvCountMax = 4;

  RenderPrimitiveType primitive = RenderPrimitiveType::Triangles;

  Vector<u32> indices;

  Vector<Tuple3f> pos;
  Vector<Tuple2f> uv[kUvCountMax];
  Vector<Color4b> color;

  Vector<Tuple3f> normal;
  Vector<Tuple3f> tangent;
  Vector<Tuple3f> binormal;

  void clear();
};

} // namespace libng
