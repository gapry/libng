#pragma once

#include <types/noncopyable.hpp>
#include <types/number.hpp>

#include <libcxx/vector.hpp>

#include <math/Color.hpp>
#include <math/Tuple/Tuple2.hpp>
#include <math/Tuple/Tuple3.hpp>

#include <renderer/type/RenderPrimitiveType.hpp>

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
